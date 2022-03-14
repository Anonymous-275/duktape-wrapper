///
/// Created by Anonymous275 on 3/14/22
/// Copyright (c) 2021-present Anonymous275 read the LICENSE file for more info.
///

#pragma once
#include <tuple>
#include <any>

struct tuple_callback {
    template<typename T>
    void operator()(T& t) const {
        t = std::any_cast<T>(NewVal);
    }
    std::any NewVal;
};

template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
find_tuple_element(int, std::tuple<Tp...> &, FuncT){}

template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
find_tuple_element(int index, std::tuple<Tp...>& t, FuncT f) {
    if (index == 0) f(std::get<I>(t));
    find_tuple_element<I + 1, FuncT, Tp...>(index-1, t, f);
}
