///
/// Created by Anonymous275 on 3/7/22
/// Copyright (c) 2021-present Anonymous275 read the LICENSE file for more info.
///

#include "duk_wrapper.h"
#include <iostream>

int main() {
    int x = 0;
    duk_wrapper::duktape engine;
    engine.push_function("clog", [&x](int val, double val2) {
        std::cout << val << " : " << val2 << std::endl;
        x = 12;
        return "hello from clog";
    });
    std::cout << "x is " << x << std::endl;
    engine.push_file("../example.js");
    std::cout << "x is " << x << std::endl;
    return 0;
}