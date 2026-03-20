#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <random>
#include <algorithm>

int main() {
    double S_0 = 100.0;
    double K = 100.0;
    double r = 0.05;
    double sigma = 0.2;
    double T = 1.0;
    int num_simulations = 1000;

    // random number generator from normal distirbution 
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0, 1);

    double Z = dist(gen);

    double S_T = S_0 * std::exp((r - 0.5 * pow(sigma, 2)) * T + sigma * std::sqrt(T) * Z);

    double call_payoff = std::max(S_T - K, 0.0);
    double put_payoff = std::max(K - S_T, 0.0);

    std::cout << "Random normal Z: " << Z << std::endl;
    std::cout << "Price at T: " << S_T << std::endl;
    std::cout << "call payoff: " << call_payoff << std::endl;
    std::cout << "put payoff: " << put_payoff << std::endl;


    return 0;

}