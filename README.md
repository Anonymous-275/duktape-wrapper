# Summary
C++17 wrapper for the [duktape](https://github.com/svaarala/duktape) library that aims to make it feel like [NodeJS](https://nodejs.org) when scripting.

# Requirements
- C++17 capable compiler
- CMake 3.0

# Usage
- Clone recursively as a submodule or build the library by just cloning it 
- Add the subdirectory in your CMakeLists (skip this if you built it yourself)
- Link it to your executable in your project
- Include "duk_wrapper.h" to use it

# Example
```cpp
#include "duk_wrapper.h" //library header include
#include <iostream>

int main() {
    int x = 0;
    duk_wrapper::duktape engine; //create and initialize duktape and all addons
    engine.push_function("clog", [&x](int val, double val2) { //you can capture
        std::cout << val << " : " << val2 << std::endl;
        x = 12;
        return "hello from clog"; //you can return virtually any basic value
    });
    std::cout << "x is " << x << std::endl; // x is still 0
    engine.push_file("example.js"); //push a file to be parsed and executed
    std::cout << "x is " << x << std::endl; // x was changed since clog was called
    return 0;
}
```
