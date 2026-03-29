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
    double call_payoff_sq_sum = 0.0;


    for (int i = 0; i < num_simulations; i++){

    double Z = dist(gen);

    double S_T1 = S_0 * std::exp((r - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * Z);
    double S_T2 = S_0 * std::exp((r - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * (-Z));


    double call_payoff_1 = std::max(S_T1 - K, 0.0);
    double call_payoff_2 = std::max(S_T2 - K, 0.0);
    
    double put_payoff_1 = std::max(K - S_T1, 0.0);
    double put_payoff_2 = std::max(K - S_T2, 0.0);

    double antithetic_call_payoff = 0.5 * (call_payoff_1 + call_payoff_2);
    double antithetic_put_payoff = 0.5 * (put_payoff_1 + put_payoff_2);
    
    call_payoff_sum += antithetic_call_payoff;
    put_payoff_sum += antithetic_put_payoff;
    call_payoff_sq_sum += antithetic_call_payoff * antithetic_call_payoff;
    }

    double average_call_payoff = call_payoff_sum / num_simulations;
    double average_put_payoff = put_payoff_sum / num_simulations;
    
    double variance_call_payoff = call_payoff_sq_sum / num_simulations - average_call_payoff * average_call_payoff;
    double std_dev_call_payoff = std::sqrt(variance_call_payoff);
    double standard_error_call = std_dev_call_payoff / std::sqrt(num_simulations);

    double confidence_interval_lower = std::exp(-r * T) * average_call_payoff - 1.96 * standard_error_call;
    double confidence_interval_upper = std::exp(-r * T) * average_call_payoff + 1.96 * standard_error_call;

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
    std::cout << "95% confidence interval for call option price: [" << confidence_interval_lower << ", " << confidence_interval_upper << "]" << std::endl;

    return 0;

}