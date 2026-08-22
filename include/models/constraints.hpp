/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <cstddef>


namespace tbaricault::models::constraints
{

    /**
     * @brief Constraint ensuring that the size of a value is at least N
     * 
     * This constraint is intended for types exposing a `size()` method.
     *
     * @tparam N Minimum allowed size
     */
    template<std::size_t N>
    struct MinSize
    {

        /**
         * @brief Validates that the value satisfies the constraint
         * 
         * @tparam T Value type
         * 
         * @param value Value to check
         * 
         * @throws std::invalid_argument If value is invalid
         */
        template<typename T>
        static constexpr void validate(const T& value);

    };

    /**
     * @brief Constraint ensuring that the size of a value is at most N
     * 
     * This constraint is intended for types exposing a `size()` method.
     *
     * @tparam N Maximum allowed size
     */
    template<std::size_t N>
    struct MaxSize
    {

        /**
         * @brief Validates that the value satisfies the constraint
         * 
         * @tparam T Value type
         * 
         * @param value Value to check
         * 
         * @throws std::invalid_argument If value is invalid
         */
        template<typename T>
        static constexpr void validate(const T& value);

    };

    /**
     * @brief Constraint ensuring that a value is equal to N
     * 
     * @tparam N Reference value used for comparison
     */
    template<auto N>
    struct EqualTo
    {

        /**
         * @brief Validates that the value satisfies the constraint
         * 
         * @tparam T Value type
         * 
         * @param value Value to check
         * 
         * @throws std::invalid_argument If value is invalid
         */
        template<typename T>
        static constexpr void validate(const T& value);

    };

    /**
     * @brief Constraint ensuring that a value is not equal to N
     * 
     * @tparam N Reference value used for comparison
     */
    template<auto N>
    struct NotEqualTo
    {

        /**
         * @brief Validates that the value satisfies the constraint
         * 
         * @tparam T Value type
         * 
         * @param value Value to check
         * 
         * @throws std::invalid_argument If value is invalid
         */
        template<typename T>
        static constexpr void validate(const T& value);

    };

    /**
     * @brief Constraint ensuring that a value is lower than N
     * 
     * @tparam N Reference value used for comparison
     */
    template<auto N>
    struct LowerThan
    {

        /**
         * @brief Validates that the value satisfies the constraint
         * 
         * @tparam T Value type
         * 
         * @param value Value to check
         * 
         * @throws std::invalid_argument If value is invalid
         */
        template<typename T>
        static constexpr void validate(const T& value);

    };

    /**
     * @brief Constraint ensuring that a value is lower or equal to N
     * 
     * @tparam N Reference value used for comparison
     */
    template<auto N>
    struct LowerOrEqualTo
    {

        /**
         * @brief Validates that the value satisfies the constraint
         * 
         * @tparam T Value type
         * 
         * @param value Value to check
         * 
         * @throws std::invalid_argument If value is invalid
         */
        template<typename T>
        static constexpr void validate(const T& value);

    };

    /**
     * @brief Constraint ensuring that a value is greater than N
     * 
     * @tparam N Reference value used for comparison
     */
    template<auto N>
    struct GreaterThan
    {

        /**
         * @brief Validates that the value satisfies the constraint
         * 
         * @tparam T Value type
         * 
         * @param value Value to check
         * 
         * @throws std::invalid_argument If value is invalid
         */
        template<typename T>
        static constexpr void validate(const T& value);

    };

    /**
     * @brief Constraint ensuring that a value is greater or equal to N
     * 
     * @tparam N Reference value used for comparison
     */
    template<auto N>
    struct GreaterOrEqualTo
    {

        /**
         * @brief Validates that the value satisfies the constraint
         * 
         * @tparam T Value type
         * 
         * @param value Value to check
         * 
         * @throws std::invalid_argument If value is invalid
         */
        template<typename T>
        static constexpr void validate(const T& value);

    };

    /**
     * @brief Constraint ensuring that a value is positive
     */
    using Positive = GreaterOrEqualTo<0>;

    /**
     * @brief Constraint ensuring that a value is negative
     */
    using Negative = LowerOrEqualTo<0>;

    /**
     * @brief Combines multiple constraints into a single validation policy
     * 
     * @tparam Constraints List of constraints composing the policy
     */
    template<typename... Constraints>
    struct Policy
    {

        /**
         * @brief Validates a value against all constraints in the policy
         *
         * @tparam T Value type
         * 
         * @param value Value to check
         * 
         * @throws std::invalid_argument If value is invalid
         */
        template<typename T>
        static constexpr void validate(const T& value);

    };

}


#include "constraints.tpp"
