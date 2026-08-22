/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <any>


namespace tbaricault::models
{

    /**
     * @brief Abstract base class for model elements
     */
    class BaseElement
    {

        public:

            /**
             * @brief Constructs an empty element
             */
            BaseElement() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Element to copy
             */
            BaseElement(const BaseElement& other) noexcept = default;

            /**
             * @brief Move constructor
             * 
             * @param other Element to move
             */
            BaseElement(BaseElement&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            virtual ~BaseElement() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Element to copy
             * 
             * @return Reference to this element
             */
            BaseElement& operator=(const BaseElement& other) noexcept = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Element to move
             * 
             * @return Reference to this element
             */
            BaseElement& operator=(BaseElement&& other) noexcept = default;

            /**
             * @brief Assigns a new value to the element
             * 
             * @param other New value
             * 
             * @return Reference to this element
             */
            BaseElement& operator=(const std::any& other);

            /**
             * @brief Sets a new value to the element
             * 
             * @param value New value
             */
            virtual void set(const std::any& value) = 0;

            /**
             * @brief Validates the element
             * 
             * @throws std::invalid_argument If element is invalid
             */
            virtual void validate() const = 0;

            /**
             * @brief Normalizes element
             * 
             * @return Element data as `std::any`
             */
            virtual std::any normalize() const = 0;

    };

}
