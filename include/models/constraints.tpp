/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "constraints.hpp"


namespace tbaricault::models::constraints
{

    template<std::size_t N>
    template<typename T>
    constexpr void MinSize<N>::validate(const T& value)
    {
        if (!(value.size() >= N))
            throw std::invalid_argument("size must be greater or equal to " + std::to_string(N));
        return;
    };

    template<std::size_t N>
    template<typename T>
    constexpr void MaxSize<N>::validate(const T& value)
    {
        if (!(value.size() <= N))
            throw std::invalid_argument("size must be lower or equal to " + std::to_string(N));
        return;
    };

    template<auto N>
    template<typename T>
    constexpr void EqualTo<N>::validate(const T& value)
    {
        if (!(value == N))
            throw std::invalid_argument("must be equal to " + tbaricault::uniconvert::convert<decltype(N), std::string>(N));
        return;
    }

    template<auto N>
    template<typename T>
    constexpr void NotEqualTo<N>::validate(const T& value)
    {
        if (!(value != N))
            throw std::invalid_argument("must be different from " + tbaricault::uniconvert::convert<decltype(N), std::string>(N));
        return;
    }

    template<auto N>
    template<typename T>
    constexpr void LowerThan<N>::validate(const T& value)
    {
        if (!(value < N))
            throw std::invalid_argument("must be lower than " + tbaricault::uniconvert::convert<decltype(N), std::string>(N));
        return;
    }

    template<auto N>
    template<typename T>
    constexpr void LowerOrEqualTo<N>::validate(const T& value)
    {
        if (!(value <= N))
            throw std::invalid_argument("must be lower than " + tbaricault::uniconvert::convert<decltype(N), std::string>(N));
        return;
    }

    template<auto N>
    template<typename T>
    constexpr void GreaterThan<N>::validate(const T& value)
    {
        if (!(value > N))
            throw std::invalid_argument("must be greater than " + tbaricault::uniconvert::convert<decltype(N), std::string>(N));
        return;
    }

    template<auto N>
    template<typename T>
    constexpr void GreaterOrEqualTo<N>::validate(const T& value)
    {
        if (!(value >= N))
            throw std::invalid_argument("must be greater than " + tbaricault::uniconvert::convert<decltype(N), std::string>(N));
        return;
    }

    template<typename... Constraints>
    template<typename T>
    constexpr void Policy<Constraints...>::validate(const T& value)
    {
        (Constraints::validate(value), ...);
        return;
    }

}
