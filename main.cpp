#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <random>

int main() {
    float S_0 = 100.0;
    float K = 100.0;
    float r = 0.05;
    float sigma = 0.2;
    float T = 1.0;
    int num_simulations = 1000;

    std::cout << "Initial stock price: " << S_0 << std::endl;
    std::cout << "Strike price: " << K << std::endl;
    std::cout << "Risk-free rate: " << r << std::endl;
    std::cout << "Volatility: " << sigma << std::endl;
    std::cout << "Time to maturity: " << T << std::endl;
    std::cout << "Number of simulations: " << num_simulations << std::endl;

    return 0;

}