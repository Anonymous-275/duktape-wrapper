///
/// Created by Anonymous275 on 3/8/22
/// Copyright (c) 2021-present Anonymous275 read the LICENSE file for more info.
///

#include "duk_wrapper.h"
#include "console/duk_console.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

duktape::duktape() : ctx(duk_create_heap_default()) {
    if (!ctx) {
        printf("Failed to create a Duktape heap.\n");
        return;
    }
    duk_console_init(ctx, 0);
}

duktape::~duktape() {
    duk_destroy_heap(ctx);
}

void duktape::push_file(const char* Name) {
    std::ifstream File(Name, std::ios::binary);
    if(File.is_open()) {
        auto Size = fs::file_size(Name);
        std::string Buffer(Size, 0);
        File.read(&Buffer[0], std::streamsize(Size));
        File.close();
        duk_push_lstring(ctx, Buffer.c_str(), Buffer.size());
    } else {
        duk_push_undefined(ctx);
    }
    if (duk_peval(ctx) != 0) {
        printf("Error: %s\n", duk_safe_to_string(ctx, -1));
    }
    duk_pop(ctx);
}

void duktape::push_function(const char *Name, duk_c_function Func, int Argc) {
    duk_push_c_function(ctx, Func, Argc);
    duk_put_global_string(ctx, Name);
}

void duktape::call_function(const char* Name) {
   // duk_safe_call(ctx, call_function, nullptr, 1, 0);
}
