# Makefile for C++ project (Do not change this file)

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Executable name
TARGET = graph.out

# Source files
SRCS = driver.cpp graph.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Dependency files
DEPS = $(SRCS:.cpp=.d)

# Compile and link
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Generate dependency files
%.d: %.cpp
	@$(CXX) $(CXXFLAGS) -MM $< | sed 's/$*\.o/& $@/g' > $@

# Include dependency files
-include $(DEPS)

.PHONY: clean

# Clean up
clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)
