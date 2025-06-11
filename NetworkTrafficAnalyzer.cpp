#include "NetworkTrafficAnalyzer.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stdexcept>

NetworkTrafficAnalyzer::NetworkTrafficAnalyzer(double tolerance, int maxIterations)
    : tolerance(tolerance), maxIterations(maxIterations) {
    std::cout << "Inicializando NetworkTrafficAnalyzer..." << std::endl;
    std::cout << "Tolerancia: " << tolerance << std::endl;
    std::cout << "Maximas iteraciones: " << maxIterations << std::endl;
}

void NetworkTrafficAnalyzer::loadTrafficData(const std::vector<std::vector<double>>& data) {
    trafficData = data;
}

double NetworkTrafficAnalyzer::getRowSum(const std::vector<double>& row, size_t skipIndex) {
    double sum = 0.0;
    for (size_t i = 0; i < row.size(); ++i) {
        if (i != skipIndex) {
            sum += std::abs(row[i]);
        }
    }
    return sum;
}

void NetworkTrafficAnalyzer::makeDiagonallyDominant(std::vector<std::vector<double>>& A, std::vector<double>& b) {
    size_t n = A.size();
    
    // Primero intentamos reordenar las filas
    for (size_t i = 0; i < n; ++i) {
        // Encontrar la fila con el elemento diagonal mas grande para esta columna
        size_t bestRow = i;
        double bestValue = std::abs(A[i][i]);
        
        for (size_t j = i + 1; j < n; ++j) {
            if (std::abs(A[j][i]) > bestValue) {
                bestValue = std::abs(A[j][i]);
                bestRow = j;
            }
        }
        
        // Intercambiar filas si es necesario
        if (bestRow != i) {
            std::swap(A[i], A[bestRow]);
            std::swap(b[i], b[bestRow]);
        }
        
        // Si el elemento diagonal es muy pequeno, intentamos hacerlo mas grande
        if (std::abs(A[i][i]) < 1e-10) {
            // Buscar la columna con el elemento mas grande en esta fila
            size_t bestCol = i;
            double maxVal = std::abs(A[i][i]);
            
            for (size_t j = i + 1; j < n; ++j) {
                if (std::abs(A[i][j]) > maxVal) {
                    maxVal = std::abs(A[i][j]);
                    bestCol = j;
                }
            }
            
            // Intercambiar columnas si es necesario
            if (bestCol != i) {
                for (size_t k = 0; k < n; ++k) {
                    std::swap(A[k][i], A[k][bestCol]);
                }
            }
        }
    }
    
    // Verificar si la matriz es diagonalmente dominante
    bool isDominant = true;
    for (size_t i = 0; i < n; ++i) {
        double diagonal = std::abs(A[i][i]);
        double sum = getRowSum(A[i], i);
        if (diagonal <= sum) {
            isDominant = false;
            break;
        }
    }
    
    // Si aun no es diagonalmente dominante, intentamos multiplicar filas
    if (!isDominant) {
        for (size_t i = 0; i < n; ++i) {
            double diagonal = std::abs(A[i][i]);
            double sum = getRowSum(A[i], i);
            if (diagonal <= sum) {
                // Multiplicar la fila por un factor para hacer el elemento diagonal mas grande
                double factor = (sum + 1.0) / diagonal;
                for (size_t j = 0; j < n; ++j) {
                    A[i][j] *= factor;
                }
                b[i] *= factor;
            }
        }
    }
}

bool NetworkTrafficAnalyzer::isDiagonallyDominant(const std::vector<std::vector<double>>& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        double diagonal = std::abs(matrix[i][i]);
        double sum = getRowSum(matrix[i], i);
        if (diagonal <= sum) {
            return false;
        }
    }
    return true;
}

double NetworkTrafficAnalyzer::calculateError(const std::vector<double>& x, const std::vector<double>& x_old) {
    double maxDiff = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        maxDiff = std::max(maxDiff, std::abs(x[i] - x_old[i]));
    }
    return maxDiff;
}

// Función para normalizar los datos
std::vector<std::vector<double>> normalizeData(const std::vector<std::vector<double>>& data,
                                             std::vector<double>& means,
                                             std::vector<double>& stds) {
    if (data.empty()) return data;
    
    size_t n = data[0].size();
    means.resize(n, 0.0);
    stds.resize(n, 0.0);
    
    // Calcular medias
    for (const auto& sample : data) {
        for (size_t i = 0; i < n; ++i) {
            means[i] += sample[i];
        }
    }
    for (double& mean : means) {
        mean /= data.size();
    }
    
    // Calcular desviaciones estándar
    for (const auto& sample : data) {
        for (size_t i = 0; i < n; ++i) {
            double diff = sample[i] - means[i];
            stds[i] += diff * diff;
        }
    }
    for (double& std : stds) {
        std = std::sqrt(std / data.size());
        if (std < 1e-10) std = 1.0; // Evitar división por cero
    }
    
    // Normalizar datos
    std::vector<std::vector<double>> normalized = data;
    for (auto& sample : normalized) {
        for (size_t i = 0; i < n; ++i) {
            sample[i] = (sample[i] - means[i]) / stds[i];
        }
    }
    
    return normalized;
}

std::vector<double> NetworkTrafficAnalyzer::normalizeSample(const std::vector<double>& sample) {
    std::vector<double> normalized = sample;
    for (size_t i = 0; i < sample.size(); ++i) {
        normalized[i] = (sample[i] - means[i]) / stds[i];
    }
    return normalized;
}

std::vector<double> NetworkTrafficAnalyzer::solveGaussSeidel(
    const std::vector<std::vector<double>>& A,
    const std::vector<double>& b) {
    
    std::cout << "Iniciando metodo de Gauss-Seidel con SOR..." << std::endl;
    int n = A.size();
    std::vector<double> x(n, 0.0);
    std::vector<double> x_old(n, 0.0);
    int iteration = 0;
    double error = tolerance + 1.0;
    double omega = 1.2; // Factor de relajación

    std::cout << "Dimension del sistema: " << n << std::endl;
    std::cout << "Tolerancia: " << tolerance << std::endl;
    std::cout << "Maximas iteraciones: " << maxIterations << std::endl;
    std::cout << "Factor de relajacion (omega): " << omega << std::endl;

    while (error > tolerance && iteration < maxIterations) {
        x_old = x;
        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    sum += A[i][j] * x[j];
                }
            }
            // Aplicar SOR
            double new_x = (b[i] - sum) / A[i][i];
            x[i] = x_old[i] + omega * (new_x - x_old[i]);
        }

        // Calcular error
        error = 0.0;
        for (int i = 0; i < n; ++i) {
            error += std::abs(x[i] - x_old[i]);
        }

        iteration++;
        if (iteration % 10 == 0) {
            std::cout << "Iteracion " << iteration << ", Error: " << error << std::endl;
        }
    }

    std::cout << "Gauss-Seidel completado en " << iteration << " iteraciones" << std::endl;
    std::cout << "Error final: " << error << std::endl;

    if (error > tolerance) {
        std::cout << "Advertencia: No se alcanzo la convergencia deseada" << std::endl;
    }

    return x;
}

bool NetworkTrafficAnalyzer::detectAnomaly(const std::vector<double>& trafficData) {
    if (weights.empty()) {
        throw std::runtime_error("El modelo no ha sido entrenado");
    }

    if (trafficData.size() != weights.size()) {
        throw std::runtime_error("Dimensiones de datos no coinciden con el modelo");
    }

    // Normalizar los datos de entrada
    auto normalizedData = normalizeSample(trafficData);

    double prediction = 0.0;
    for (size_t i = 0; i < normalizedData.size(); ++i) {
        prediction += normalizedData[i] * weights[i];
    }

    // Calcular el error de prediccion
    double actualValue = normalizedData.back();
    double error = std::abs(prediction - actualValue);
    double relativeError = error / std::abs(actualValue);

    // Si el error relativo es mayor que un umbral, consideramos que es una anomalia
    return relativeError > 0.3; // 30% de error relativo
}

void NetworkTrafficAnalyzer::updateModel(const std::vector<std::vector<double>>& trainingData) {
    std::cout << "Iniciando actualizacion del modelo..." << std::endl;
    std::cout << "Numero de muestras de entrenamiento: " << trainingData.size() << std::endl;
    
    if (trainingData.empty()) {
        throw std::runtime_error("No hay datos de entrenamiento");
    }

    // Normalizar los datos
    std::cout << "Normalizando datos..." << std::endl;
    auto normalizedData = normalizeData(trainingData, means, stds);

    // Obtener dimensiones
    int n = normalizedData[0].size() - 1;  // -1 porque el ultimo elemento es el resultado
    std::cout << "Dimension del sistema: " << n << std::endl;

    // Construir matriz A y vector b
    std::vector<std::vector<double>> A(n, std::vector<double>(n, 0.0));
    std::vector<double> b(n, 0.0);

    std::cout << "Construyendo sistema de ecuaciones..." << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0.0;
            for (const auto& sample : normalizedData) {
                sum += sample[i] * sample[j];
            }
            A[i][j] = sum;
        }
        
        double sum = 0.0;
        for (const auto& sample : normalizedData) {
            sum += sample[i] * sample.back();
        }
        b[i] = sum;
    }

    std::cout << "Sistema de ecuaciones construido." << std::endl;
    std::cout << "Dimensiones de A: " << A.size() << "x" << A[0].size() << std::endl;
    std::cout << "Dimension de b: " << b.size() << std::endl;

    // Resolver el sistema usando Gauss-Seidel
    std::cout << "Iniciando resolucion del sistema..." << std::endl;
    weights = solveGaussSeidel(A, b);
    std::cout << "Sistema resuelto exitosamente." << std::endl;
    std::cout << "Pesos calculados: ";
    for (double w : weights) {
        std::cout << w << " ";
    }
    std::cout << std::endl;
}

void NetworkTrafficAnalyzer::setTolerance(double newTolerance) {
    tolerance = newTolerance;
}

void NetworkTrafficAnalyzer::setMaxIterations(int newMaxIterations) {
    maxIterations = newMaxIterations;
}

double NetworkTrafficAnalyzer::getTolerance() const {
    return tolerance;
}

int NetworkTrafficAnalyzer::getMaxIterations() const {
    return maxIterations;
} 