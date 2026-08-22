/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <tbaricault/templates.hpp>


namespace tbaricault::models
{

    /**
     * @brief Struct representing a named model field
     * 
     * @tparam Name Field name
     * @tparam Field Field type
     */
    template<tbaricault::templates::FixedString Name, typename Field>
    struct FieldInfo
    {

        /**
         * @brief Field type
         */
        using Type = Field;


        /**
         * @brief Field name
         */
        static constexpr auto name = Name;

    };

}
