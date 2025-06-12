#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <fstream>

int main() {
    // --- 1. Explicacion Inicial ---
    std::cout << " Simulacion del Rendimiento de una Aplicacion Segun el Numero de Usuarios Concurrentes" << std::endl;
    std::cout << "------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Este programa modelara y predecira el tiempo de respuesta de una aplicacion " << std::endl;
    std::cout << "a medida que mas usuarios la usen al mismo tiempo." << std::endl;
    std::cout << "Utilizaremos datos simulados y el metodo matematico de Gauss-Seidel." << std::endl;
    std::cout << "\nPresione Enter para comenzar..." << std::endl;
    std::cin.ignore(); // Limpiar el buffer si hay un Enter previo
    std::cin.get();

    // --- 2. Datos Simulados ---
    std::cout << "\n---  Datos Simulados de Rendimiento ---" << std::endl;
    std::cout << "¿Desea usar los datos por defecto o ingresar sus propios datos?" << std::endl;
    std::cout << "1. Usar datos por defecto (y = 2x^2 + x + 2)" << std::endl;
    std::cout << "2. Ingresar datos personalizados" << std::endl;
    std::cout << "Ingrese su opcion (1 o 2): ";
    
    int opcion;
    std::cin >> opcion;
    std::cin.ignore(); // Limpiar el buffer después de leer el número

    DatosRendimiento datos;
    if (opcion == 1) {
        // Datos por defecto
        datos = {
            {1, 2, 3, 4, 5},      // Usuarios (valores pequeños)
            {5, 12, 23, 38, 57}   // Tiempo de respuesta (ms) (exactamente y = 2x^2 + x + 2)
        };
    } else {
        // Datos personalizados
        std::cout << "\nIngrese el numero de puntos de datos (entre 5 y 15): ";
        int n;
        std::cin >> n;
        n = std::max(5, std::min(15, n)); // Asegurar que n esté entre 5 y 15

        std::vector<double> usuarios(n);
        std::vector<double> tiempos(n);

        std::cout << "\nIngrese los datos (usuarios y tiempo de respuesta en ms):" << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << "Punto " << (i + 1) << ":" << std::endl;
            std::cout << "Numero de usuarios: ";
            std::cin >> usuarios[i];
            std::cout << "Tiempo de respuesta (ms): ";
            std::cin >> tiempos[i];
        }

        datos = {usuarios, tiempos};
    }

    std::cout << "\nDatos de rendimiento que usaremos:" << std::endl;
    std::cout << "\nUsuarios | Tiempo de respuesta (ms)" << std::endl;
    std::cout << "---------|--------------------------" << std::endl;
    for (size_t i = 0; i < datos.usuarios.size(); ++i) {
        std::cout << std::setw(8) << datos.usuarios[i] << " | " << std::setw(24) << datos.tiempoRespuesta[i] << std::endl;
    }
    std::cout << "\nPresione Enter para continuar con los calculos..." << std::endl;
    std::cin.get();

    // --- 3. Calculo de Sumatorias --- 
    std::cout << "\n--- 📊 Calculo de Sumatorias para Minimos Cuadrados ---" << std::endl;
    std::cout << "Para encontrar el mejor modelo que se ajuste a estos datos, necesitamos calcular varias sumatorias." << std::endl;
    std::vector<double> sumatorias = calcularSumatorias(datos);
    
    double sum_x = sumatorias[0];
    double sum_y = sumatorias[1];
    double sum_x2 = sumatorias[2];
    double sum_x3 = sumatorias[3];
    double sum_x4 = sumatorias[4];
    double sum_xy = sumatorias[5];
    double sum_x2y = sumatorias[6];
    double n = datos.usuarios.size();

    std::cout << "\nSumatorias calculadas:" << std::endl;
    std::cout << "  Sum(x)   = " << sum_x << std::endl;
    std::cout << "  Sum(y)   = " << sum_y << std::endl;
    std::cout << "  Sum(x^2) = " << sum_x2 << std::endl;
    std::cout << "  Sum(x^3) = " << sum_x3 << std::endl;
    std::cout << "  Sum(x^4) = " << sum_x4 << std::endl;
    std::cout << "  Sum(xy)  = " << sum_xy << std::endl;
    std::cout << "  Sum(x^2y) = " << sum_x2y << std::endl;
    std::cout << "  n        = " << n << std::endl;

    std::cout << "\nPresione Enter para armar el sistema de ecuaciones..." << std::endl;
    std::cin.get();

    // --- 4. Armado del Sistema de Ecuaciones --- 
    std::cout << "\n--- Armado del Sistema de Ecuaciones Lineales ---" << std::endl;
    std::cout << "Ahora construiremos un sistema de 3 ecuaciones con 3 incognitas (a, b, c) " << std::endl;
    std::cout << "para el modelo f(x) = ax^2 + bx + c." << std::endl;

    std::vector<std::vector<double>> A(3, std::vector<double>(3));
    std::vector<double> b(3);

    // Ecuacion 1: a*Sum(x^4) + b*Sum(x^3) + c*Sum(x^2) = Sum(x^2y)
    A[0][0] = sum_x4;
    A[0][1] = sum_x3;
    A[0][2] = sum_x2;
    b[0] = sum_x2y;

    // Ecuacion 2: a*Sum(x^3) + b*Sum(x^2) + c*Sum(x) = Sum(xy)
    A[1][0] = sum_x3;
    A[1][1] = sum_x2;
    A[1][2] = sum_x;
    b[1] = sum_xy;

    // Ecuacion 3: a*Sum(x^2) + b*Sum(x) + c*n = Sum(y)
    A[2][0] = sum_x2;
    A[2][1] = sum_x;
    A[2][2] = n;
    b[2] = sum_y;

    std::cout << "\nEl sistema de ecuaciones es:" << std::endl;
    imprimirMatriz("Matriz A", A);
    imprimirVector("Vector b", b);

    std::cout << "\nPresione Enter para resolver el sistema con Gauss-Seidel..." << std::endl;
    std::cin.get();

    // --- 5. Resolucion con Gauss-Seidel --- 
    std::cout << "\n--- Resolucion del Sistema con Gauss-Seidel ---" << std::endl;
    std::cout << "Vamos a encontrar los valores de a, b y c de forma iterativa." << std::endl;
    std::cout << "Observa como los valores se ajustan en cada paso:" << std::endl;

    double tolerancia = 0.0001;
    int maxIteraciones = 1000;
    std::vector<double> coeficientes = gaussSeidel(A, b, tolerancia, maxIteraciones);
    
    double a = coeficientes[0];
    double b_coef = coeficientes[1]; // Renombrado para evitar conflicto con vector b
    double c = coeficientes[2];

    std::cout << "\nPresione Enter para ver el modelo ajustado..." << std::endl;
    std::cin.get();

    // --- 6. Modelo Ajustado --- 
    std::cout << "\n--- Modelo de Rendimiento Ajustado ---" << std::endl;
    std::cout << "Hemos encontrado los coeficientes para el modelo que mejor describe el rendimiento:" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "f(x) = " << a << "x^2 + " << b_coef << "x + " << c << std::endl;

    std::cout << "\nDonde:" << std::endl;
    std::cout << "  x = Numero de usuarios concurrentes" << std::endl;
    std::cout << "  f(x) = Tiempo de respuesta esperado en milisegundos" << std::endl;

    // --- 8. Grafico de Texto en Terminal ---
    std::cout << "\n--- 📉 Grafico de Rendimiento en Terminal (ASCII Art) ---" << std::endl;
    std::cout << "Este es un grafico aproximado de la funcion en la terminal:" << std::endl;
    std::cout << "(Curva: *, Datos Originales: o)" << std::endl;

    const int plotWidth = 70;  // Ancho del grafico en caracteres
    const int plotHeight = 20; // Alto del grafico en lineas

    std::vector<std::string> plot(plotHeight, std::string(plotWidth, ' '));

    // Determinar rangos para escalar
    double minX = datos.usuarios.empty() ? 0 : datos.usuarios[0];
    double maxX = datos.usuarios.empty() ? 10 : datos.usuarios.back();
    if (maxX < 10) maxX = 10; // Asegurar un minimo para el rango X
    
    // Extender el rango X para la curva
    maxX *= 1.2;

    double minY = 0, maxY = 0;

    // Calcular minY y maxY de la funcion dentro del rango de usuarios
    bool firstY = true;
    for (double x = minX; x <= maxX; x += (maxX - minX) / plotWidth) {
        double y_val = a * std::pow(x, 2) + b_coef * x + c;
        if (firstY) {
            minY = y_val;
            maxY = y_val;
            firstY = false;
        } else {
            if (y_val < minY) minY = y_val;
            if (y_val > maxY) maxY = y_val;
        }
    }

    // Asegurar que maxY no sea cero para evitar division por cero en el escalado
    if (minY == maxY) { // Si todos los puntos son iguales
        minY -= 1; // Para que haya un rango, aunque sea pequeno
        maxY += 1;
    }
    if (minY < 0) minY = 0; // El tiempo de respuesta no puede ser negativo

    // Dibujar el grafico
    for (int i = 0; i < plotHeight; ++i) {
        plot[i][0] = '|'; // Eje Y
    }
    for (int j = 0; j < plotWidth; ++j) {
        plot[plotHeight - 1][j] = '-'; // Eje X
    }
    plot[plotHeight - 1][0] = '+'; // Origen

    // Dibujar la funcion
    for (int j = 0; j < plotWidth; ++j) {
        double x_scaled = minX + (maxX - minX) * j / plotWidth;
        double y_func = a * std::pow(x_scaled, 2) + b_coef * x_scaled + c;

        int y_pos = static_cast<int>((y_func - minY) / (maxY - minY) * (plotHeight - 1));
        y_pos = plotHeight - 1 - y_pos; // Invertir para que el origen este abajo

        if (y_pos >= 0 && y_pos < plotHeight && j >= 0 && j < plotWidth) {
            plot[y_pos][j] = '*';
        }
    }

    // Dibujar los datos originales
    for (size_t i = 0; i < datos.usuarios.size(); ++i) {
        double x_data = datos.usuarios[i];
        double y_data = datos.tiempoRespuesta[i];

        int x_pos = static_cast<int>((x_data - minX) / (maxX - minX) * (plotWidth - 1));
        int y_pos = static_cast<int>((y_data - minY) / (maxY - minY) * (plotHeight - 1));
        y_pos = plotHeight - 1 - y_pos;

        if (x_pos >= 0 && x_pos < plotWidth && y_pos >= 0 && y_pos < plotHeight) {
            plot[y_pos][x_pos] = 'o';
        }
    }

    // Imprimir el grafico
    for (int i = 0; i < plotHeight; ++i) {
        std::cout << plot[i] << std::endl;
    }

    // Etiquetas de los ejes (muy basicas)
    std::cout << "0" << std::string(plotWidth / 2 - 1, ' ') << "Usuarios" << std::string(plotWidth - plotWidth / 2 - 8, ' ') << static_cast<int>(maxX) << std::endl;
    std::cout << "Tiempo de Respuesta (ms)" << std::endl;

    std::cout << "\nPresione Enter para continuar con la prediccion..." << std::endl;
    std::cin.get();

    // --- 7. Prediccion de Rendimiento ---
    std::cout << "\n--- Prediccion de Rendimiento ---" << std::endl;
    std::cout << "Ahora puedes ingresar diferentes numeros de usuarios para ver la prediccion del tiempo de respuesta." << std::endl;
    std::cout << "Ingresa 0 para salir en cualquier momento." << std::endl;
    
    int usuariosInput;
    while (true) {
        std::cout << "\nIngrese numero de usuarios (0 para salir): ";
        std::cin >> usuariosInput;

        if (usuariosInput == 0) {
            break; // Salir del bucle si el usuario ingresa 0
        }

        double tiempoEstimado = a * std::pow(usuariosInput, 2) + b_coef * usuariosInput + c;
        std::cout << std::fixed << std::setprecision(0);
        std::cout << "\nPara " << usuariosInput << " usuarios, el tiempo estimado de respuesta es: " << tiempoEstimado << " ms" << std::endl;
        std::cout << "Ejemplo de interpretacion real: 'si tenes " << usuariosInput << " usuarios, el sistema tardara ~" << tiempoEstimado << " ms'" << std::endl;
    }

    std::cout << "\n--- FIN DEL PROGRAMA ---" << std::endl;
    std::cout << "¿Desea volver a ejecutar el programa con nuevos datos?" << std::endl;
    std::cout << "1. Si" << std::endl;
    std::cout << "2. No" << std::endl;
    std::cout << "Ingrese su opcion (1 o 2): ";
    
    int reiniciar;
    std::cin >> reiniciar;
    std::cin.ignore(); // Limpiar el buffer después de leer el número

    if (reiniciar == 1) {
        std::cout << "\n\n\n"; // Espacios para separar las ejecuciones
        main(); // Volver a ejecutar el programa
    } else {
        std::cout << "\nPresione Enter para salir..." << std::endl;
        std::cin.get();
    }

    return 0;
} 