#!/bin/bash

# Check if a library type argument is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 {static|shared}"
    exit 1
fi

LIB_TYPE=$1
SRC_FILES="*.cpp"  # Change this to your actual source files
OUTPUT="mylibrary"

# Create static library
if [ "$LIB_TYPE" == "static" ]; then
    echo "Building static library..."
    g++ -c $SRC_FILES               # Compile source files into object files
    ar rcs lib$OUTPUT.a *.o         # Create static library
    g++ -o myapp main.cpp -L. -l$OUTPUT   # Link the application with the static library

# Create shared library
elif [ "$LIB_TYPE" == "shared" ]; then
    echo "Building shared library..."
    g++ -fPIC -c $SRC_FILES         # Compile source files as position-independent code (for shared libs)
    g++ -shared -o lib$OUTPUT.so *.o # Create shared library
    g++ -o myapp main.cpp -L. -l$OUTPUT   # Link the application with the shared library

# Handle invalid input
else
    echo "Invalid argument: $LIB_TYPE"
    echo "Usage: $0 {static|shared}"
    exit 1
fi

# Clean up object files after compilation
rm -f *.o

echo "Build complete."
