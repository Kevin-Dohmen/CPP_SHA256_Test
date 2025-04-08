# Output directory
OUT_DIR := ./build
$(shell mkdir -p $(OUT_DIR))

# Other directories
SRC_DIR := ./src
INC_DIR := ./include

# compilers:
# g++					 : GNU C++ compiler
# x86_64-w64-mingw32-g++ : MinGW-w64 C++ compiler for 64-bit Windows
# i686-w64-mingw32-g++	 : MinGW-w64 C++ compiler for 32-bit Windows

# Compiler and flags
CXX := x86_64-w64-mingw32-g++ # Compiler
CXXFLAGS := \
	-Wall -Wextra \
	-O2 -frename-registers -flto -funroll-loops \
	-std=c++17 \
	-static-libgcc -static-libstdc++

# Target executable
TARGET := $(OUT_DIR)/main.exe

# Source and header files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
HEADERS := $(wildcard $(INC_DIR)/*.h)

# Object files
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.o)

# Default target
all: $(TARGET)

# Link object files to create the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@

# Clean up build files
clean:
	@echo "Cleaning up..."
	rm -rf $(OUT_DIR)

# Phony targets
.PHONY: all clean
