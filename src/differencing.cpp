#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<vector<double>> CDS(double rho,
                           double gamma,
                           double L,
                           double u,
                           int n) {
    double a_E, a_W, a_P, deltax;
    vector<vector<double>> A(n, vector<double>(n, 0.0)); 

    // Calculate coefficients for the central differencing scheme
    deltax = L/n;
    a_E = gamma / deltax - 0.5 * (rho * u);
    a_W = gamma / deltax + 0.5 * (rho * u);
    a_P = a_E + a_W;

    // Fill matrix
    for (int i = 1; i < n - 1; i++) {
        A[i][i - 1] = -a_W;   
        A[i][i] = a_P;        
        A[i][i + 1] = -a_E;   
    }

    // Correct matrix for Dirichlet boundary conditions
    A[0][0] = 1.0;            
    A[n - 1][n - 1] = 1.0;   

    return A;
}

vector<vector<double>> UDS(double rho,
                           double gamma,
                           double L,
                           double u,
                           int n) {
    double a_E, a_W, a_P, deltax;
    vector<vector<double>> A(n, vector<double>(n, 0.0)); 

    // Calculate coefficients for the upwind differencing scheme
    deltax = L/n;
    a_E = gamma / deltax + max((-1*rho*u),0.0);
    a_W = gamma / deltax + max((rho*u),0.0);
    a_P = a_E + a_W;

    // Fill matrix
    for (int i = 1; i < n - 1; i++) {
        A[i][i - 1] = -a_W;   // West coefficient
        A[i][i] = a_P;        // Center coefficient
        A[i][i + 1] = -a_E;   // East coefficient
    }

    // Correct matrix for Dirichlet boundary conditions
    A[0][0] = 1.0;            
    A[n - 1][n - 1] = 1.0;    

    return A;
}

vector<vector<double>> PLDS(double rho,
                           double gamma,
                           double L,
                           double u,
                           double Pe,
                           int n) {
    double a_E, a_W, a_P, deltax;
    vector<vector<double>> A(n, vector<double>(n, 0.0)); // Initialize matrix A with zeros

    // Calculate coefficients for the power law differencing scheme
    deltax = L/n;
    a_E = (gamma / deltax) * max(pow((1 - 0.1 * abs(Pe)), 5), 0.0) + max(-rho * u, 0.0);
    a_W = (gamma / deltax) * max(pow((1 - 0.1 * abs(Pe)), 5), 0.0) + max(rho * u, 0.0);
    a_P = a_E + a_W;

    // Fill matrix
    for (int i = 1; i < n - 1; i++) {
        A[i][i - 1] = -a_W;   
        A[i][i] = a_P;        
        A[i][i + 1] = -a_E;   
    }

    // Correct matrix for Dirichlet boundary conditions
    A[0][0] = 1.0;           
    A[n - 1][n - 1] = 1.0;   
    return A;
}