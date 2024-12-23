#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <tuple> 

using namespace std;


vector<double> TDMA(const vector<vector<double>>& A, const vector<double>& rhs) {
    int n = A.size();

    // Initialise diagonals
    vector<double> a(n - 1); // Sub-diagonal
    vector<double> b(n);     // Main diagonal
    vector<double> c(n - 1); // Super-diagonal

    // Extract diagonals from the matrix A
    for (int i = 0; i < n; ++i) {
        b[i] = A[i][i]; 
        if (i > 0) {
            a[i - 1] = A[i][i - 1]; 
        }
        if (i < n - 1) {
            c[i] = A[i][i + 1]; 
        }
    }

    // TDMA solution
    vector<double> c_prime(n); 
    vector<double> d_prime(n); 
    vector<double> x(n);       

    // Forward elimination
    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            c_prime[i] = c[i] / b[i];
            d_prime[i] = rhs[i] / b[i];
        } else {
            double denom = b[i] - a[i - 1] * c_prime[i - 1];
            c_prime[i] = c[i] / denom;
            d_prime[i] = (rhs[i] - a[i - 1] * d_prime[i - 1]) / denom;
        }
    }

    // Backward substitution
    for (int i = n - 1; i >= 0; --i) {
        if (i == n - 1) {
            x[i] = d_prime[i];
        } else {
            x[i] = d_prime[i] - c_prime[i] * x[i + 1];
        }
    }

    return x;
}

vector<double> GaussianElimination(vector<vector<double>>& matrix, vector<double>& rhs) {
    int n = matrix.size();
    vector<double> x(n, 0); 
    vector<vector<double>> Z(n, vector<double>(n + 1));

    // Create augmented matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Z[i][j] = matrix[i][j]; 
        }
        Z[i][n] = rhs[i]; 
    }

    // Partial Pivot
    for (int i = 0; i < n; ++i) {
        for (int p = i + 1; p < n; ++p) {
            if (fabs(Z[p][i]) > fabs(Z[i][i])) {
                swap(Z[i], Z[p]);
            }
        }
        // Check for singularity - should be avoided with partial pivot
        if (fabs(Z[i][i]) < 1e-12) {
            cerr << "Error: Division by zero or singular matrix." << endl;
            return {};
        }

        // Foward elimination process
        for (int j = i + 1; j < n; ++j) {
            double scaling_factor = Z[j][i] / Z[i][i];
            for (int k = i; k <= n; ++k) {
                Z[j][k] -= scaling_factor * Z[i][k];
            }
        }
    }

    // Back substitution
    for (int i = n - 1; i >= 0; --i) {
        x[i] = Z[i][n];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= Z[i][j] * x[j];
        }
        x[i] /= Z[i][i];
    }

    return x;
}
