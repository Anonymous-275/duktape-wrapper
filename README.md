# Summary
C++11 wrapper for the [duktape](https://github.com/svaarala/duktape) library that aims to make it feel like [NodeJS](https://nodejs.org) when scripting

# Requirements
- C++11 capable compiler
- CMake 3.0

# Usage
- Clone recursively as a submodule or build the library by just cloning it 
- Add the subdirectory in your CMakeLists (skip this if you built it yourself)
- Link it to your executable in your project
- Include "duk_wrapper.h" to use it.

# Example
```cpp
#include "duk_wrapper.h"

int main() {
    duktape engine; //create and initialize duktape and all adons
    engine.push_file("example.js"); //push a file to be parsed and executed
    return 0;
}
```
