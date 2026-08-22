/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "BaseElement.hpp"


namespace tbaricault::models
{

    /**
     * @brief Abstract base class for fields
     */
    class BaseField
        : public BaseElement
    {

        public:

            /**
             * @brief Constructs an empty field
             */
            BaseField() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Field to copy
             */
            BaseField(const BaseField& other) noexcept = default;

            /**
             * @brief Move constructor
             * 
             * @param other Field to move
             */
            BaseField(BaseField&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            virtual ~BaseField() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Field to copy
             * 
             * @return Reference to this field
             */
            BaseField& operator=(const BaseField& other) noexcept = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Field to move
             * 
             * @return Reference to this field
             */
            BaseField& operator=(BaseField&& other) noexcept = default;

    };

}
