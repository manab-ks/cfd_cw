// linalg.h
#ifndef LINALG_H
#define LINALG_H

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <tuple> 


// Function declarations
std::vector<double> TDMA(const std::vector<std::vector<double>>& A, const std::vector<double>& rhs);

std::vector<double> GaussianElimination(std::vector<std::vector<double>>& matrix, std::vector<double>& rhs);

#endif // LINALG_H