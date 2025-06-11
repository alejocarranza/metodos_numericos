#include "NetworkTrafficAnalyzer.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <random>
#include <thread>
#include <chrono>
#include <windows.h>

// Funcion para generar datos de trafico normal simulados
std::vector<double> generarTraficoNormal() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    // Metricas tipicas de trafico de red
    static std::normal_distribution<> paquetes(5000, 500);     // Paquetes por segundo (tipico en una red pequena)
    static std::normal_distribution<> bytes(250000, 25000);    // Bytes por segundo (aproximadamente 2 Mbps)
    static std::normal_distribution<> conexiones(100, 10);     // Conexiones TCP activas
    static std::normal_distribution<> latencia(50, 5);         // Latencia en milisegundos
    static std::normal_distribution<> errores(5, 1);           // Errores de red por minuto

    return {
        paquetes(gen),     // Paquetes por segundo
        bytes(gen),        // Bytes por segundo
        conexiones(gen),   // Conexiones TCP activas
        latencia(gen),     // Latencia (ms)
        errores(gen)       // Errores por minuto
    };
}

// Funcion para generar trafico anomalo (simulando diferentes tipos de ataques)
std::vector<double> generarTraficoAnomalo() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    // Simulamos diferentes tipos de ataques
    int tipoAtaque = gen() % 3;  // 0: DDoS, 1: Port Scan, 2: Inyeccion SQL
    
    switch (tipoAtaque) {
        case 0: {  // DDoS
            static std::normal_distribution<> paquetes(50000, 5000);   // Aumento masivo de paquetes
            static std::normal_distribution<> bytes(2500000, 250000);  // Aumento masivo de bytes
            static std::normal_distribution<> conexiones(1000, 100);   // Muchas conexiones
            static std::normal_distribution<> latencia(200, 20);       // Latencia alta
            static std::normal_distribution<> errores(50, 5);          // Muchos errores
            
            return {
                paquetes(gen),
                bytes(gen),
                conexiones(gen),
                latencia(gen),
                errores(gen)
            };
        }
        case 1: {  // Port Scan
            static std::normal_distribution<> paquetes(10000, 1000);   // Aumento moderado de paquetes
            static std::normal_distribution<> bytes(500000, 50000);    // Aumento moderado de bytes
            static std::normal_distribution<> conexiones(500, 50);     // Muchas conexiones fallidas
            static std::normal_distribution<> latencia(100, 10);       // Latencia moderada
            static std::normal_distribution<> errores(30, 3);          // Errores de conexion
            
            return {
                paquetes(gen),
                bytes(gen),
                conexiones(gen),
                latencia(gen),
                errores(gen)
            };
        }
        default: {  // Inyeccion SQL
            static std::normal_distribution<> paquetes(8000, 800);     // Aumento leve de paquetes
            static std::normal_distribution<> bytes(400000, 40000);    // Aumento leve de bytes
            static std::normal_distribution<> conexiones(200, 20);     // Conexiones normales
            static std::normal_distribution<> latencia(150, 15);       // Latencia alta
            static std::normal_distribution<> errores(20, 2);          // Errores de base de datos
            
            return {
                paquetes(gen),
                bytes(gen),
                conexiones(gen),
                latencia(gen),
                errores(gen)
            };
        }
    }
}

void printTrafico(const std::vector<double>& trafico) {
    // Limpiar la consola
    system("cls");
    
    std::cout << "=== MONITOR DE TRAFICO DE RED ===" << std::endl;
    std::cout << "Metricas de trafico:" << std::endl;
    std::cout << "  Paquetes por segundo: " << std::fixed << std::setprecision(0) << trafico[0] << std::endl;
    std::cout << "  Bytes por segundo: " << std::fixed << std::setprecision(0) << trafico[1] << " (" 
              << std::fixed << std::setprecision(2) << (trafico[1] * 8.0 / 1000000.0) << " Mbps)" << std::endl;
    std::cout << "  Conexiones TCP activas: " << std::fixed << std::setprecision(0) << trafico[2] << std::endl;
    std::cout << "  Latencia: " << std::fixed << std::setprecision(1) << trafico[3] << " ms" << std::endl;
    std::cout << "  Errores por minuto: " << std::fixed << std::setprecision(0) << trafico[4] << std::endl;
}

void alertaAnomalia() {
    // Hacer sonar el altavoz del sistema
    Beep(1000, 500);  // Frecuencia 1000Hz por 500ms
    Beep(2000, 500);  // Frecuencia 2000Hz por 500ms
}

int main() {
    // Crear instancia del analizador
    NetworkTrafficAnalyzer analyzer(0.0001, 100);

    // Generar datos de entrenamiento (trafico normal)
    std::vector<std::vector<double>> trainingData;
    std::cout << "Generando datos de entrenamiento (trafico normal)..." << std::endl;
    
    for (int i = 0; i < 20; ++i) {
        auto trafico = generarTraficoNormal();
        trafico.push_back(trafico[1]);
        trainingData.push_back(trafico);
        std::cout << "Muestra " << (i + 1) << " generada." << std::endl;
        Sleep(500);  // Usar Sleep de Windows en lugar de this_thread
    }

    // Entrenar el modelo
    std::cout << "\nEntrenando el modelo con datos normales..." << std::endl;
    analyzer.updateModel(trainingData);
    Sleep(2000);  // 2 segundos de pausa

    // Simular monitoreo continuo
    std::cout << "\nIniciando monitoreo continuo..." << std::endl;
    std::cout << "Presione Ctrl+C para detener el monitoreo" << std::endl;
    Sleep(2000);  // 2 segundos de pausa

    int contador = 0;
    while (true) {
        contador++;
        auto trafico = (contador % 10 == 5) ? generarTraficoAnomalo() : generarTraficoNormal();
        printTrafico(trafico);
        
        bool esAnomalia = analyzer.detectAnomaly(trafico);
        std::cout << "\nEstado: " << (esAnomalia ? "ANOMALIA DETECTADA!" : "Trafico normal") << std::endl;
        
        if (esAnomalia) {
            alertaAnomalia();
            std::cout << "\nPresione Enter para continuar...";
            std::cin.get();
        }
        
        Sleep(1000);  // 1 segundo de pausa
    }

    return 0;
} 