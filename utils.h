#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include <iomanip>

// Estructura para almacenar los datos de rendimiento
struct DatosRendimiento {
    std::vector<double> usuarios;
    std::vector<double> tiempoRespuesta;
};

// Calcula los sumatorios necesarios para el metodo de minimos cuadrados
std::vector<double> calcularSumatorias(const DatosRendimiento& datos);

// Resuelve un sistema de ecuaciones lineales 3x3 usando el metodo de Gauss-Seidel
// Retorna un vector con los coeficientes [a, b, c]
std::vector<double> gaussSeidel(const std::vector<std::vector<double>>& A,
                                  const std::vector<double>& b,
                                  double tolerancia,
                                  int maxIteraciones);

// Funcion para imprimir un vector (util para depuracion y visualizacion)
void imprimirVector(const std::string& nombre, const std::vector<double>& vec);

// Funcion para imprimir una matriz 3x3 (util para visualizacion del sistema)
void imprimirMatriz(const std::string& nombre, const std::vector<std::vector<double>>& mat);

#endif // UTILS_H 