///
/// Created by Anonymous275 on 3/7/22
/// Copyright (c) 2021-present Anonymous275 read the LICENSE file for more info.
///

#include "duk_wrapper.h"

int clog(duk_context* ctx) {
    printf("print func -> %s\n", duk_safe_to_string(ctx, 0));
    return 0;
}

int main() {
    duktape engine;
    engine.push_function("clog", clog, 1);
    engine.push_file("../example.js");
    return 0;
}