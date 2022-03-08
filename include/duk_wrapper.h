///
/// Created by Anonymous275 on 3/8/22
/// Copyright (c) 2021-present Anonymous275 read the LICENSE file for more info.
///

#pragma once
#include "duktape.h"
class duktape {
public:
    duktape();
    ~duktape();
    void push_file(const char* Name);
    void push_function(const char* Name, duk_c_function Func, int Argc);
private:
    duk_context* ctx;
};
