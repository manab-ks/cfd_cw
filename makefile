# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = $(SRC_DIR)
RESULT_DIR = results

# Target executable
TARGET = $(BUILD_DIR)/simulation

# Source files
SRCS = $(SRC_DIR)/simulation.cpp $(SRC_DIR)/differencing.cpp $(SRC_DIR)/linalg.cpp $(SRC_DIR)/analytical.cpp

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Ensure build directory exists
$(shell mkdir -p $(BUILD_DIR))

# Instructions for building the target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile individual .cpp files into .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(TARGET) $(OBJS)
	rm -f $(RESULT_DIR)/*.txt