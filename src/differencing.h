// differencing.h
#ifndef DIFFERENCING_H
#define DIFFERENCING_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// Declare the UDS function
std::vector<std::vector<double>> CDS(double rho,
                                     double gamma,
                                     double L,
                                     double u,
                                     int n);

std::vector<std::vector<double>> UDS(double rho,
                                     double gamma,
                                     double L,
                                     double u,
                                     int n);
std::vector<std::vector<double>> PLDS(double rho,
                           double gamma,
                           double L,
                           double u,
                           double Pe,
                           int n);

#endif // DIFFERENCING_H