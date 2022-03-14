///
/// Created by Anonymous275 on 3/8/22
/// Copyright (c) 2021-present Anonymous275 read the LICENSE file for more info.
///

#include "duk_wrapper.h"
#include "console/duk_console.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
namespace duk_wrapper {

    duktape::duktape() : ctx(duk_create_heap_default()) {
        functions.reserve(20);
        if (!ctx) {
            printf("Failed to create a Duktape heap.\n");
            return;
        }
        duk_console_init(ctx, 0);
    }

    int duktape::entry(duk_context* context) {
        return functions.at(duk_get_current_magic(context) + 128)->call(context);
    }

    duktape::~duktape() {
        duk_destroy_heap(ctx);
    }

    void duktape::push_file(const char *Name) {
        std::ifstream File(Name, std::ios::binary);
        if (File.is_open()) {
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

    void duktape::call_function(const char *Name) {
        // duk_safe_call(ctx, call_function, nullptr, 1, 0);
    }

    std::any duktape::get_val(duk_context* context, const std::type_index& type, int idx) {
        if(type == typeid(int)) {
            return int(duk_to_int(context, idx));
        } else if(type == typeid(int32_t)) {
            return int32_t(duk_to_int32(context, idx));
        } else if(type == typeid(float)) {
            return float(duk_to_number(context, idx));
        } else if(type == typeid(double)) {
            return double(duk_to_number(context, idx));
        } else if(type == typeid(const char*)) {
            return (const char*)(duk_to_string(context, idx));
        } else if(type == typeid(char*)) {
            return (char*)(duk_to_string(context, idx));
        } else if(type == typeid(std::string)) {
            return std::string(duk_to_string(context, idx));
        } else if(type == typeid(bool)) {
            return bool(duk_to_boolean(context, idx));
        } else if(type == typeid(unsigned int)) {
            return (unsigned int)(duk_to_uint(context, idx));
        } else if(type == typeid(uint16_t)) {
            return uint16_t(duk_to_uint16(context, idx));
        } else if(type == typeid(uint32_t)) {
            return uint32_t(duk_to_uint32(context, idx));
        } else if(type == typeid(void*)) {
            return (void*)(duk_to_pointer(context, idx));
        }
        return "invalid type";
    }
    void duktape::push_val(duk_context* context, const std::type_index& type, const std::any& val) {
        if(type == typeid(int)) {
            duk_push_int(context, duk_int_t(std::any_cast<int>(val)));
        } else if(type == typeid(int32_t)) {
            duk_push_int(context, duk_int_t(std::any_cast<int32_t>(val)));
        } else if(type == typeid(float)) {
            duk_push_number(context, duk_double_t(std::any_cast<float>(val)));
        } else if(type == typeid(double)) {
            duk_push_number(context, duk_double_t(std::any_cast<double>(val)));
        } else if(type == typeid(const char*)) {
            duk_push_string(context, std::any_cast<const char*>(val));
        } else if(type == typeid(char*)) {
            duk_push_string(context, std::any_cast<char*>(val));
        } else if(type == typeid(std::string)) {
            duk_push_string(context, std::any_cast<std::string>(val).c_str());
        } else if(type == typeid(bool)) {
            duk_push_boolean(context, duk_bool_t(std::any_cast<bool>(val)));
        } else if(type == typeid(unsigned int)) {
            duk_push_uint(context, duk_uint_t(std::any_cast<unsigned int>(val)));
        } else if(type == typeid(uint16_t)) {
            duk_push_uint(context, duk_uint_t(std::any_cast<uint16_t>(val)));
        } else if(type == typeid(uint32_t)) {
            duk_push_uint(context, duk_uint_t(std::any_cast<uint32_t>(val)));
        } else if(type == typeid(void*)) {
            duk_push_pointer(context, std::any_cast<void*>(val));
        }
    }
}
