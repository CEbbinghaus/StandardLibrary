#pragma once
#include <type_traits>

static class Math{
public:
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    static T clamp(T value, T min, T max){
        if(value < min)return min;
        if(value > max)return max;
        return value;
    }
};