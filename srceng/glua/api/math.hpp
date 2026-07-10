#pragma once
#include <concepts>

namespace math{
    template <typename T>
    concept int_or_float = std::is_integral_v<T> || std::is_floating_point_v<T>;

    template<int_or_float T>
    [[nodiscard]] constexpr T abs(T x) noexcept {
        return x >= T{0} ? x : -x;
    }

    template<std::floating_point T>
    [[nodiscard]] constexpr T lerp(T t, T from, T to) noexcept {
        return from + (to - from) * t;
    }

    template<int_or_float T>
    [[nodiscard]] constexpr T clamp(T input, T min, T max) noexcept {
        if (input < min) return min;
        if (input > max) return max;
        return input;
    }

    template<std::floating_point T>
    [[nodiscard]] constexpr T approach(T current, T target, T change) noexcept {
        if (math::abs(target - current) <= math::abs(change))
            return target;
        return current + ( current < target ? change : -change );
    }

    template<std::floating_point T>
    [[nodiscard]] constexpr T remap(T val, T inMin, T inMax, T outMin, T outMax) noexcept {
        if (inMin == inMax) return outMin;
        T t = (val - inMin) / (inMax - inMin);
        return lerp(t, outMin, outMax);
    }

}
