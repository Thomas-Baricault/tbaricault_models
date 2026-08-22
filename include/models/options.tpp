/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "options.hpp"


namespace tbaricault::models::options
{

    template<typename... Options>
    template<typename T>
    constexpr bool Policy<Options...>::contains()
    {
        return (tbaricault::templates::contains<T, Options...>::value);
    }

}
