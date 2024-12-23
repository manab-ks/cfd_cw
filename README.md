# Computational Fluid Dynamics Coursework 1

## Overview
This repository contains the code and documentation for **Computational Fluid Dynamics (CFD) Coursework 1**, part of the MECH70015 module.
## Repository Structure
- `src/`: Source code for the simulations.
- `build/`: Contains executables and object files generated during compilation.
- `results/`: Stores raw simulation output files.
- `analysis/`: Python scripts and Jupyter notebooks for post-processing and visualizing results.

## Requirements
To run the code and analyse results, you’ll need the following:
- **Python 3.x**
- **Jupyter Notebook** (to run `.ipynb` files)
- **NumPy** and **Matplotlib** Python libraries
- **C++ compiler** supporting **C++17** 

## Usage Instructions
### 1. Setup and Compilation
1. Open the `Makefile` and confirm that the `CXX` variable is set to the C++ compiler available on your system. By default, it is set to `g++`.
2. Navigate to the repository's root directory in your terminal:
   ```bash
   cd /path/to/repository
   ```
3. Compile the code:
   ```bash
   make
   ```
4. Run the simulation:
   ```bash
   ./build/simulation
   ```
   Follow the on-screen instructions to configure and run simulations.

### 2. Rebuilding After Code Changes
If you modify the source code, clear the previous build and results before recompiling, this should also be done when generating new results to avoid clutter which can cause unexpected behavour in the post-processing:
```bash
make clean
make
```

### 3. Results
Simulation results are saved in the `results/` directory. Files are named according to the method and number of nodes used during the simulation.

### 4. Post-Processing
To analyse and visualize the results, open the corresponding Jupyter Notebook in the `analysis/` directory. For example:
```bash
jupyter notebook analysis/your_notebook.ipynb
```

## Notes
- Ensure all dependencies are installed before running the code.
- Always use `make clean` before recompiling the code after changes.

## Contact
For questions, feedback, or issues, please contact [ms620@ic.ac.uk](mailto:ms620@ic.ac.uk).
