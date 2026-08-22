/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <any>
#include <optional>

#include "constraints.hpp"
#include "options.hpp"

#include "BaseField.hpp"


namespace tbaricault::models
{

    /**
     * @brief Field containing a value and configurable with constraints and options
     * 
     * @tparam T Value type
     * @tparam Contraints Constraints policy
     * @tparam Options Options policy
     */
    template<typename T, typename Constraints = constraints::Policy<>, typename Options = options::Policy<>>
    class Field final
        : public BaseField
    {

        public:

            /**
             * @brief Default constructor
             */
            Field() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Field to copy
             */
            Field(const Field& other) = default;

            /**
             * @brief Move constructor
             * 
             * @param other Field to move
             */
            Field(Field&& other) noexcept = default;

            /**
             * @brief Constructs a field with a value
             * 
             * @param value Value to set
             */
            Field(const std::any& value);

            /**
             * @brief Destructor
             */
            virtual ~Field() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Field to copy
             * 
             * @return Reference to this field
             */
            Field& operator=(const Field& other);

            /**
             * @brief Move assignment operator
             * 
             * @param other Field to move
             * 
             * @return Reference to this field
             */
            Field& operator=(Field&& other) noexcept = default;

            /**
             * @brief Equivalent to `get()`
             */
            operator const T&() const;

            /**
             * @brief Equivalent to `get()`
             */
            operator T&();

            /**
             * @brief Checks whether the stored value is null
             * 
             * @return `true` if null, `false` otherwise
             */
            bool isNull() const noexcept;

            /**
             * @brief Returns the stored value
             * 
             * @return Constant reference to the stored value
             * 
             * @throws std::runtime_error If field has no value
             */
            const T& get() const;

            /**
             * @brief Returns the stored value
             * 
             * @return Reference to the stored value
             * 
             * @throws std::runtime_error If field is readonly or has no value
             */
            T& get();

            /**
             * @brief Sets a new value to the field performing basics conversion if possible
             * 
             * @param value New value
             * 
             * @throws std::invalid_argument If value is invalid
             * @throws std::runtime_error If field is readonly
             */
            virtual void set(const std::any& value) override;

            /**
             * @brief Validates the field value
             * 
             * @throws std::invalid_argument If value is invalid
             */
            virtual void validate() const override;

            /**
             * @brief Normalizes field value
             * 
             * @return Value as `std::any`
             */
            virtual std::any normalize() const override;


        private:

            /**
             * @brief Whether this field has been setted at least once
             */
            bool _setted = false;

            /**
             * @brief Field value
             */
            std::optional<T> _value;

    };


    /**
     * @brief Base case for an non field types
     * 
     * @tparam T Type to inspect
     */
    template<typename T>
    struct FieldTraits
    {

        /**
         * @brief Whether the type is recognized as a field
         */
        static constexpr bool isField = false;

    };

    /**
     * @brief Type traits specialization for `Field`
     * 
     * @tparam T Value type
     * @tparam Contraints Constraints policy
     * @tparam Options Options policy
     */
    template<typename T, typename Constraints, typename Options>
    struct FieldTraits<Field<T, Constraints, Options>>
    {

        /**
         * @brief Container value type
         */
        using ValueType = T;


        /**
         * @brief Whether the type is recognized as a field
         */
        static constexpr bool isField = true;

    };

}


#include "Field.tpp"
