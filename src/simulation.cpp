#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <fstream>
#include "linalg.h"
#include "differencing.h"
#include "analytical.h"

using namespace std;

int main() {
    // Deafult problem parameters
    double rho = 1.0, gamma = 1.0, u = 10.0, L = 1.0, phi_0 = 100, phi_L = 20;

    // Ask the user if they would like to enter their own simulation parameters
    cout << "Enter 0 to execute simulation with default parameters, otherwise enter 1 for custom parameters selection: ";
    int param_choice;
    cin >> param_choice;

    if (param_choice == 1) {
        cout << "The default value is bracketed (...) for your reference.\n";
        cout << "Enter value for rho (1.0): ";
        cin >> rho;
        cout << "Enter value for gamma (1.0): ";
        cin >> gamma;
        cout << "Enter value for u (1.0): ";
        cin >> u;
        cout << "Enter value for L (1.0): ";
        cin >> L;
        cout << "Enter Dirichilet condition at x = 0 (100.0): ";
        cin >> phi_0;
        cout << "Enter Dirichilet condition at x = L (20.0): ";
        cin >> phi_L;
    }

    // User input for iterative or single run
    cout << "Enter 0 to execute for a single number of nodes, otherwise enter 1 to iterate over multiple numbers of nodes: ";
    int iterate_choice;
    cin >> iterate_choice;

    vector<int> n_values; 

    if (iterate_choice == 1) {
        cout << "Enter minimum number of nodes, please ensure this is greater than 3: ";
        int n_min;
        cin >> n_min;

        cout << "Enter maximum number of nodes: ";
        int n_max;
        cin >> n_max;

        cout << "Enter base of logarithmic progression: ";
        int log_base;
        cin >> log_base;

        // Calculate logarithmic steps (linear stepping quickly becomes unfeasible)
        for (int n = n_min; n <= n_max; n *= log_base) {
            n_values.push_back(n); 
        }
    } else {
        cout << "Enter number of nodes: ";
        int n_single;
        cin >> n_single;
        n_values.push_back(n_single);
    }

    // Get user input for method and solver
    cout << "Enter 0 to execute all schemes, 1 for CDS, 2 for UDS and 3 for PLDS: ";
    int method_choice;
    cin >> method_choice;

    cout << "Enter 0 to solve using the Thomas Algorithm, otherwise enter 1 to solve via Gaussian Elimination: ";
    int solver_choice;
    cin >> solver_choice;

    // Loop over selected values of n
    for (int n : n_values) {
        double deltax = L / n;
        double Pe = fabs((rho * u * deltax) / gamma);

        // Boundary conditions incoporated into rhs vector
        vector<double> b(n, 0.0);
        b[0] = phi_0;
        b[n - 1] = phi_L;

        // Solutions file named after the method used followed by the number of nodes
        vector<pair<string, string>> methods = {
            {"CDS", "./results/cds" + to_string(n) + ".txt"},
            {"UDS", "./results/uds" + to_string(n) + ".txt"},
            {"PLDS", "./results/plds" + to_string(n) + ".txt"}
        };

        // Analytical solution (always computed)
        analytical(phi_0, phi_L, rho, u, gamma, L, n, "./results/anly" + to_string(n) + ".txt");

        for (size_t i = 0; i < methods.size(); ++i) {
            if (method_choice != 0 && method_choice != static_cast<int>(i + 1)) {
                continue;
            }

            string method_name = methods[i].first;
            string file_path = methods[i].second;

            cout << "Solving using " << method_name << " for n = " << n << "..." << endl;

            vector<vector<double>> A;
            if (method_name == "CDS") {
                A = CDS(rho, gamma, L, u, n);
            } else if (method_name == "UDS") {
                A = UDS(rho, gamma, L, u, n);
            } else if (method_name == "PLDS") {
                A = PLDS(rho, gamma, L, u, Pe, n);
            }

            vector<double> x;
            if (solver_choice == 0) {
                // Solve with TDMA
                x = TDMA(A, b);
            } else if (solver_choice == 1) {
                // Solve with Gaussian Elimination
                x = GaussianElimination(A, b);
            }

            // Write solution file
            ofstream file(file_path);
            if (file.is_open()) {
                // Write parameters as the first line
                file << "Delta x = " << deltax << " m" 
                     << ", Velocity = " << u << " m/s" 
                     << ", Diffusion Constant = " << gamma << " m^2/s" 
                     << ", Density = " << rho << " kg/m^3" 
                     << ", Peclet Number = " << Pe 
                     << endl
                     << endl;

                // Write the solution
                for (size_t j = 0; j < x.size(); ++j) {
                    file << j * deltax << "," << x[j] << endl;
                }
                file.close();
                cout << "Solution saved to " << file_path << endl;
            } else {
                cerr << "Error: Unable to open file " << file_path << endl;
            }
        }
    }

    return 0;
}
