/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <cstddef>

#include <tbaricault/templates.hpp>


namespace tbaricault::models::options
{

    /**
     * @brief Marker option enabling optional behavior
     */
    struct Optional {};

    /**
     * @brief Marker option enabling read-only behavior
     */
    struct Readonly {};

    /**
     * @brief Marker option enabling strict conversion behavior
     */
    struct Strict {};

    /**
     * @brief Defines a default value option
     * 
     * @tparam V Default value associated with this option
     */
    template<auto V>
    struct Default
    {

        /**
         * @brief Default value
         */
        static constexpr auto value = V;

    };

    /**
     * @brief Extracts the default option type from a list of options
     *
     * @tparam Options List of options to inspect
     */
    template<typename... Options>
    struct DefaultTraits
    {

        /**
         * @brief Default type
         */
        using Type = void;

    };

    /**
     * @brief Recursive specialization used to search for a default option
     * 
     * @tparam First Current option being inspected
     * @tparam Rest Remaining options
     */
    template<typename First, typename... Rest>
    struct DefaultTraits<First, Rest...>
    {

        /**
         * @brief Default type
         */
        using Type = typename DefaultTraits<Rest...>::Type;

    };

    /**
     * @brief Specialization matching a Default option
     * 
     * @tparam V Default value
     * @tparam Rest Remaining options after the default option
     */
    template<auto V, typename... Rest>
    struct DefaultTraits<Default<V>, Rest...>
    {

        /**
         * @brief Default type
         */
        using Type = Default<V>;

    };

    /**
     * @brief Represents a compile-time collection of options
     * 
     * @tparam Options Options composing the policy
     */
    template<typename... Options>
    struct Policy
    {

        /**
         * @brief Default type option
         * 
         * If no Default option is provided, this type resolves to void.
         */
        using DefaultType = typename DefaultTraits<Options...>::Type;


        /**
         * @brief Checks whether a specific option is contained in the policy
         * 
         * @tparam T Option type to search for
         *
         * @return `true` if the option is present, `false` otherwise
         */
        template<typename T>
        static constexpr bool contains();

    };
}


#include "options.tpp"
