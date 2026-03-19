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

    // random number generator from normal distirbution 
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dist(0, 1);

    float Z = dist(gen);

    std::cout << "Random normal Z: " << Z << std::endl;
    
    
    return 0;

}