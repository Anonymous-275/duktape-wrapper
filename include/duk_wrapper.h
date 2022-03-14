///
/// Created by Anonymous275 on 3/8/22
/// Copyright (c) 2021-present Anonymous275 read the LICENSE file for more info.
///

#pragma once
#include "duktape.h"
#include "dynamic_tuple.h"
#include <type_traits>
#include <functional>
#include <typeindex>
#include <iostream>
#include <array>
#include <any>

namespace duk_wrapper {
    class duktape {
    public:
        duktape();
        ~duktape();
        void push_file(const char *Name);
        void call_function(const char *Name);

        template<typename TFunc>
        void push_function(const char* Name, TFunc Func) {
            std::function func(Func);
            functions.emplace_back(std::make_unique<duk_function<decltype(func)>>(ctx, Name, func));
        }

    private:
        template<typename T>
        struct function_traits;
        template<typename R, typename ...Args>
        struct function_traits<std::function<R(Args...)>> {
            static const size_t nargs = sizeof...(Args);
            template<typename T = std::tuple<Args...>, std::enable_if_t<(std::tuple_size<T>::value > 0)> * = nullptr>
            static inline std::array<std::type_index, nargs> args() {
                return {std::type_index(typeid(Args))...};
            }
            template<typename T = std::tuple<Args...>, std::enable_if_t<(std::tuple_size<T>::value == 0)> * = nullptr>
            static inline std::array<std::type_index, nargs> args() {
                return {typeid(void)};
            }
            typedef std::tuple<Args...> arguments;
            typedef R return_type;
        };

        struct func_base {
            virtual ~func_base() = default;
            virtual int call(duk_context* context){return 0;};
        };

        template<typename T>
        struct duk_function : func_base {
            duk_function() = delete;
            duk_function(duk_context* ctx, const char* Name, T Func) : func(std::move(Func)) {
                ret = typeid(typename func_type::return_type) != typeid(void);
                duk_push_c_lightfunc(ctx, entry, func_type::nargs, func_type::nargs, func_id++);
                duk_put_global_string(ctx, Name);
            };
            template<typename Type, typename Args, std::enable_if_t<std::is_same<Type, void>::value> * = nullptr>
            inline int handle(Args& Tuple) {
                std::apply(func, Tuple);
                return 0;
            }
            template<typename Type, typename Args, std::enable_if_t<!std::is_same<Type, void>::value> * = nullptr>
            inline Type handle(Args& Tuple) {
                return std::apply(func, Tuple);
            }
            int call(duk_context* context) override {
                typename func_type::arguments args_tuple{};
                auto args_index = func_type::args();

                for(int i = 0; i < func_type::nargs; i++) {
                    find_tuple_element(i, args_tuple, tuple_callback{get_val(context, args_index[i], i)});
                }
                auto val = handle<return_type>(args_tuple);
                if(ret) {
                    push_val(context, typeid(return_type), val);
                    return 1;
                }
                return 0;
            }
            using func_type = function_traits<T>;
            using return_type = typename func_type::return_type;
            bool ret;
            T func;
        };
        static inline int func_id = -128;
        static int entry(duk_context* context);
        static inline std::vector<std::unique_ptr<func_base>> functions;
        static std::any get_val(duk_context* context, const std::type_index& type, int idx);
        static void push_val(duk_context* context, const std::type_index& type, const std::any& val);
        duk_context* ctx;
    };
}