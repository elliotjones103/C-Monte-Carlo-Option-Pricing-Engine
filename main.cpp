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
    int num_simulations = 1000000;

    // random number generator from normal distirbution 
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0, 1);

    // Monte carlo simulation for prices

    double call_payoff_sum = 0.0;
    double put_payoff_sum = 0.0;

    for (int i = 0; i < num_simulations; i++) {

    double Z = dist(gen);

    double S_T = S_0 * std::exp((r - 0.5 * pow(sigma, 2)) * T + sigma * std::sqrt(T) * Z);

    double call_payoff = std::max(S_T - K, 0.0);
    double put_payoff = std::max(K - S_T, 0.0);

    call_payoff_sum += call_payoff;
    put_payoff_sum += put_payoff;

    }

    double average_call_payoff = call_payoff_sum / num_simulations;
    double average_put_payoff = put_payoff_sum / num_simulations;
    
    double call_option_price = std::exp(-r * T) * average_call_payoff;
    double put_option_price = std::exp(-r * T) * average_put_payoff;
    
    double put_call_parity_lhs = call_option_price + K * std::exp(-r * T);
    double put_call_parity_rhs = put_option_price + S_0;

    // Analytical Black Scholes Prices

    double d_1 = (std::log(S_0 / K) + (r + ((sigma * sigma) / 2)) * T) / (sigma * std::sqrt(T));
    double d_2 = d_1 - sigma * std::sqrt(T);
    double N_d1 = 0.5 * (1 + erf(d_1 / std::sqrt(2)));
    double N_d2 = 0.5 * (1 + erf(d_2 / std::sqrt(2)));
    double neg_N_d1 = 0.5 * (1 + erf(-d_1 / std::sqrt(2)));
    double neg_N_d2 = 0.5 * (1 + erf(-d_2 / std::sqrt(2)));

    double C_ABS = S_0 * N_d1 - K * std::exp(-r * T) * N_d2;
    double P_ABS = K * std::exp(-r * T) * neg_N_d2 - S_0 * neg_N_d1;


    std::cout << "MC call option price: " << call_option_price << std::endl;
    std::cout << "MC put option price: " << put_option_price << std::endl;
    std::cout << "put call parity?: " << put_call_parity_lhs << " = " << put_call_parity_rhs << std::endl;
    std::cout << " Analytical BS call price: " << C_ABS << std::endl;
    std::cout << " Analytical BS put price: " << P_ABS << std::endl;

    return 0;

}