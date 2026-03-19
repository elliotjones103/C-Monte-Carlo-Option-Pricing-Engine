# C++ Monte Carlo Option Pricing Engine

A C++ project for pricing financial derivatives using Monte Carlo simulation.

The goal of this project is to build a fast and well structured pricing engine in C++, starting with European options under geometric Brownian motion and extending it with variance reduction, Greeks estimation, and performance benchmarking against Python implementations.

## Overview

Monte Carlo methods are widely used in quantitative finance for derivative pricing and risk estimation, especially when closed form solutions are unavailable or difficult to apply.

This project is designed as both a learning exercise in modern C++ and a practical quantitative finance project. It focuses on building a reusable simulation framework, validating results against analytical benchmarks such as Black Scholes, and exploring the performance advantages of C++ over Python for computational finance tasks.

## Features

- Monte Carlo pricing for European call and put options
- Geometric Brownian motion simulation under the risk neutral measure
- Confidence intervals for Monte Carlo estimates
- Variance reduction using antithetic variates
- Greeks estimation using bump and reprice methods
- Modular C++ design with clear separation of pricing, simulation, and statistics
- Benchmarking against equivalent Python implementations
- Extensions planned for path dependent options and parallelisation

## Mathematical Framework

Under the risk neutral measure, the terminal asset price is modelled as

$\[
S_T = S_0 \exp \left( \left(r - \frac{1}{2}\sigma^2\right)T + \sigma \sqrt{T} Z \right)
\]$

where $\( Z \sim N(0,1) \).$

For a European call option, the payoff is

$\[
\max(S_T - K, 0)
\]$

and the Monte Carlo price estimate is

$\[
V_0 \approx e^{-rT} \frac{1}{N} \sum_{i=1}^{N} \max(S_T^{(i)} - K, 0)
\]$

The same framework can be adapted for put options and, later, more complex derivatives.
