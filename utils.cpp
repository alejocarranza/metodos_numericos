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

// Funcion para imprimir una matriz aumentada [A|b] (util para visualizacion del proceso de eliminacion Gaussiana)
void imprimirMatrizAumentada(const std::string& nombre, const std::vector<std::vector<double>>& A, const std::vector<double>& b) {
    std::cout << nombre << ":" << std::endl;
    std::cout << std::fixed << std::setprecision(15);
    for (size_t i = 0; i < A.size(); ++i) {
        std::cout << "[ ";
        for (double val : A[i]) {
            std::cout << val << " ";
        }
        std::cout << "| " << b[i] << " ]" << std::endl;
    }
    std::cout << std::endl;
}

// Resuelve un sistema de ecuaciones lineales 3x3 usando el metodo de Eliminacion Gaussiana
// Retorna un vector con los coeficientes [a, b, c]
std::vector<double> gaussianElimination(std::vector<std::vector<double>> A,
                                        std::vector<double> b) {
    int n = A.size();
    std::vector<double> x(n); // Vector para almacenar los coeficientes a, b, c

    std::cout << "\n--- Proceso de Eliminacion Gaussiana (paso a paso) ---" << std::endl;
    imprimirMatrizAumentada("Matriz Aumentada Inicial", A, b);

    // Eliminacion hacia adelante
    for (int k = 0; k < n; ++k) { // Pivote
        std::cout << "Paso " << k + 1 << ": Pivoteando y Eliminando columna " << k + 1 << std::endl;
        // Encontrar el pivote mas grande para mejorar la estabilidad numerica (pivoteo parcial)
        int i_max = k;
        double v_max = std::abs(A[k][k]);
        for (int i = k + 1; i < n; ++i) {
            if (std::abs(A[i][k]) > v_max) {
                v_max = std::abs(A[i][k]);
                i_max = i;
            }
        }

        // Intercambiar la fila actual con la fila del pivote mas grande
        if (i_max != k) {
            std::cout << "  -> Intercambiando Fila " << k + 1 << " con Fila " << i_max + 1 << std::endl;
            std::swap(A[k], A[i_max]);
            std::swap(b[k], b[i_max]);
            imprimirMatrizAumentada("  Matriz despues de pivoteo", A, b);
        }

        // Manejo de caso donde el pivote es cero despues del pivoteo
        if (A[k][k] == 0) {
            std::cerr << "Error: Division por cero o matriz singular en Eliminacion Gaussiana. No se puede resolver." << std::endl;
            return std::vector<double>(); // Retornar vector vacio o lanzar excepcion
        }

        // Hacer ceros debajo del pivote
        for (int i = k + 1; i < n; ++i) {
            double factor = A[i][k] / A[k][k];
            std::cout << "  El factor para Fila " << i + 1 << " es: " << std::fixed << std::setprecision(15) << A[i][k] << " / " << std::fixed << std::setprecision(15) << A[k][k] << " = " << std::fixed << std::setprecision(15) << factor << std::endl;
            std::cout << "  -> Fila " << i + 1 << " = Fila " << i + 1 << " - (" << std::fixed << std::setprecision(15) << factor << ") * Fila " << k + 1 << std::endl;
            for (int j = k; j < n; ++j) {
                A[i][j] -= factor * A[k][j];
            }
            b[i] -= factor * b[k];
        }
        imprimirMatrizAumentada("  Matriz despues de eliminacion de columna " + std::to_string(k + 1), A, b);
    }

    std::cout << "--- Eliminacion hacia adelante completada ---" << std::endl;
    imprimirMatrizAumentada("Matriz en forma Triangular Superior", A, b);

    std::cout << "\n--- Sustitucion hacia atras (calculo de coeficientes) ---" << std::endl;
    // Sustitucion hacia atras
    for (int i = n - 1; i >= 0; --i) {
        if (A[i][i] == 0) { // Manejo de caso donde un elemento diagonal es cero despues de eliminacion
            std::cerr << "Error: Matriz singular despues de eliminacion. No se puede resolver." << std::endl;
            return std::vector<double>(); // Retornar vector vacio o lanzar excepcion
        }
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j) {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
        std::cout << "  -> x[" << i + 1 << "] = " << std::fixed << std::setprecision(15) << x[i] << std::endl;
    }

    std::cout << "\n--- Proceso de Eliminacion Gaussiana finalizado ---" << std::endl;

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