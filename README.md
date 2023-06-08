# Markowitz Portfolio Optimization

This project aims to implement the Markowitz portfolio optimization algorithm to determine the optimal allocation of assets in a portfolio. The optimization algorithm seeks to maximize returns while minimizing risk by considering the covariance matrix of asset returns.

## Table of Contents

- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The Markowitz portfolio optimization algorithm, developed by Harry Markowitz in the 1950s, is a widely used method for constructing efficient investment portfolios. It takes into account the expected returns and covariances of different assets to find an optimal asset allocation that maximizes returns for a given level of risk.

This project provides an implementation of the Markowitz portfolio optimization algorithm in C++. It includes classes for managing portfolios, calculating mean returns and covariance matrices, and performing the optimization calculations.

## Project Structure

The project has the following structure:

- `portfolioOptimizer.h`: Header file containing the `Optimizer` class, responsible for performing the portfolio optimization.
- `matrix.h`: Header file containing the `Matrix` class, used for matrix operations.
- `portfolioOptimizer.cpp`: Implementation file for the `Optimizer` class.
- `matrix.cpp`: Implementation file for the `Matrix` class.
- `main.cpp`: Main entry point of the program.

## Dependencies

The project has the following dependencies:

- C++ Standard Library

## Usage

To use the Markowitz portfolio optimization algorithm in your own project, follow these steps:

1. Include the necessary header files in your code:

   ```cpp
   #include "portfolioOptimizer.h"
   #include "matrix.h"
