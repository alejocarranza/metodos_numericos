#ifndef NETWORK_TRAFFIC_ANALYZER_H
#define NETWORK_TRAFFIC_ANALYZER_H

#include <vector>
#include <string>
#include <cmath>

class NetworkTrafficAnalyzer {
private:
    std::vector<std::vector<double>> trafficData;
    std::vector<double> modelCoefficients;
    double tolerance;
    int maxIterations;
    std::vector<double> weights;
    
    // Parámetros de normalización
    std::vector<double> means;
    std::vector<double> stds;
    
    // Helper methods
    bool isDiagonallyDominant(const std::vector<std::vector<double>>& matrix);
    double calculateError(const std::vector<double>& x, const std::vector<double>& x_old);
    void makeDiagonallyDominant(std::vector<std::vector<double>>& A, std::vector<double>& b);
    double getRowSum(const std::vector<double>& row, size_t skipIndex);
    std::vector<double> normalizeSample(const std::vector<double>& sample);
    
public:
    NetworkTrafficAnalyzer(double tolerance = 0.0001, int maxIterations = 100);
    
    // Core functionality
    void loadTrafficData(const std::vector<std::vector<double>>& data);
    std::vector<double> solveGaussSeidel(const std::vector<std::vector<double>>& A, 
                                       const std::vector<double>& b);
    bool detectAnomaly(const std::vector<double>& currentTraffic);
    void updateModel(const std::vector<std::vector<double>>& newData);
    
    // Getters and setters
    void setTolerance(double newTolerance);
    void setMaxIterations(int newMaxIterations);
    double getTolerance() const;
    int getMaxIterations() const;
};

#endif // NETWORK_TRAFFIC_ANALYZER_H 