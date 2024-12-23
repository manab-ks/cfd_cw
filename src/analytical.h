#ifndef ANALYTICAL_H
#define ANALYTICAL_H

#include <vector>
#include <cmath>
#include <fstream>
#include <string>


void analytical(double phi0, double phiL, double rho, double u, double gamma, double L, int n, const std::string& filePath);

#endif // ANALYTICAL_H