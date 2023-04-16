### Requirements
- A C/C++ Compiler: GCC, Clang
- CMake

### Build Instructions

If you are on a POSIX type system, then to build the project you can run the following.
```
mkdir build
cd build
cmake ..
cmake --build .
```

### Run Tests

In the same `build` directory you can run the following.
```
cmake ..
cmake --build .
ctest --verbose
```