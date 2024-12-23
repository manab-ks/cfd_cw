#include <vector>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

// Computes the analytical solution at discrete points for the 1D convection-diffusion equation, given parameters
void analytical(double phi0, double phiL, double rho, double u, double gamma, double L, int n, const string& filePath) {
    vector<double> phi(n, 0.0); 
    double deltax = L / (n ); 
    double Pe = fabs((rho * u * deltax) / gamma);
    double expDenominator = exp(rho * u * L / gamma) - 1.0;

    for (int i = 0; i < n; ++i) {
        double x = i * deltax;
        double expNumerator = exp(rho * u * x / gamma) - 1.0;
        phi[i] = phi0 + (expNumerator / expDenominator) * (phiL - phi0);
    }


    ofstream file(filePath);
    if (file.is_open()) {
    file << "Delta x = " << deltax << " m"
        << ", Velocity  = " << u << " m/s"
        << ", Diffusion Constant  = " << gamma << " m^2/s"
        << ", Density  = " << rho << " kg/m^3"
        << ", Peclet Number = " << Pe 
        << endl
        << endl;

        for (int i = 0; i < n; ++i) {
            double x = i * deltax; 
            file << x << "," << phi[i] << endl;
        }
        file.close();
    } else {
        throw runtime_error("Error: Unable to open file " + filePath);
    }
}

            