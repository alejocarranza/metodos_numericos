#include "utils.h"

// Calcula los sumatorios necesarios para el metodo de minimos cuadrados
std::vector<double> calcularSumatorias(const DatosRendimiento& datos) {
    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_x2 = 0.0; // x^2
    double sum_x3 = 0.0; // x^3
    double sum_x4 = 0.0; // x^4
    double sum_xy = 0.0;
    double sum_x2y = 0.0; // x^2 * y

    for (size_t i = 0; i < datos.usuarios.size(); ++i) {
        double x = datos.usuarios[i];
        double y = datos.tiempoRespuesta[i];
        
        sum_x += x;
        sum_y += y;
        sum_x2 += x * x;
        sum_x3 += x * x * x;
        sum_x4 += x * x * x * x;
        sum_xy += x * y;
        sum_x2y += x * x * y;
    }

    return {sum_x, sum_y, sum_x2, sum_x3, sum_x4, sum_xy, sum_x2y};
}

// Resuelve un sistema de ecuaciones lineales 3x3 usando el metodo de Gauss-Seidel
// Retorna un vector con los coeficientes [a, b, c]
std::vector<double> gaussSeidel(const std::vector<std::vector<double>>& A,
                                  const std::vector<double>& b,
                                  double tolerancia,
                                  int maxIteraciones) {
    int n = A.size();
    std::vector<double> x(n, 0.0); // Valores iniciales de a, b, c
    std::vector<double> x_old(n, 0.0);
    double error = tolerancia + 1.0; // Para asegurar que el bucle se ejecute al menos una vez
    int iteracion = 0;

    std::cout << "Iniciando metodo de Gauss-Seidel..." << std::endl;
    std::cout << std::fixed << std::setprecision(4);

    while (error > tolerancia && iteracion < maxIteraciones) {
        x_old = x; // Guardar los valores de la iteracion anterior

        for (int i = 0; i < n; ++i) {
            double sum_sigma = 0.0;
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    sum_sigma += A[i][j] * x[j];
                }
            }
            x[i] = (b[i] - sum_sigma) / A[i][i];
        }

        // Calcular el error (diferencia máxima entre las iteraciones)
        error = 0.0;
        for (int i = 0; i < n; ++i) {
            error = std::max(error, std::abs(x[i] - x_old[i]));
        }

        iteracion++;
        // Imprimir resultados parciales para el usuario
        if (iteracion % 1 == 0 || error <= tolerancia || iteracion == maxIteraciones) { // Imprimir cada iteracion
            std::cout << "Iteracion " << iteracion << ": ";
            std::cout << "a = " << x[0] << "  b = " << x[1] << "  c = " << x[2];
            std::cout << "  Error: " << error << std::endl;
        }
    }

    if (error <= tolerancia) {
        std::cout << "Convergencia alcanzada en " << iteracion << " iteraciones." << std::endl;
    } else {
        std::cout << "Maximas iteraciones alcanzadas. No se alcanzo la convergencia deseada." << std::endl;
    }

    return x;
}

// Funcion para imprimir un vector (util para depuracion y visualizacion)
void imprimirVector(const std::string& nombre, const std::vector<double>& vec) {
    std::cout << nombre << ": [ ";
    for (double val : vec) {
        std::cout << std::fixed << std::setprecision(4) << val << " ";
    }
    std::cout << "]" << std::endl;
}

// Funcion para imprimir una matriz 3x3 (util para visualizacion del sistema)
void imprimirMatriz(const std::string& nombre, const std::vector<std::vector<double>>& mat) {
    std::cout << nombre << ":" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    for (const auto& row : mat) {
        std::cout << "[ ";
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << "]" << std::endl;
    }
} 