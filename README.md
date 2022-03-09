# Summary
C++11 wrapper for the [duktape](https://github.com/svaarala/duktape) library that aims to make it feel like [NodeJS](https://nodejs.org).

Simply add this project as a cmake subdirectory or build the library then include "duk_wrapper.h" in your project to use it.

# Example
```cpp
#include "duk_wrapper.h"

int main() {
    duktape engine; //create and initialize duktape and all adons
    engine.push_file("example.js"); //push a file to be parsed and executed
    return 0;
}
```
