/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "BaseModel.hpp"


namespace tbaricault::models
{

    template<tbaricault::templates::FixedString Name>
    constexpr decltype(auto) BaseModel::get()
    {
        static_assert(false, "field not found");
    }

}
