/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <any>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

#include <tbaricault/templates.hpp>

#include "BaseElement.hpp"
#include "BaseField.hpp"


namespace tbaricault::models
{

    /**
     * @brief Abstract base class for models
     */
    class BaseModel
        : public BaseElement
    {

        public:

            /**
             * @brief Default constructor
             */
            BaseModel() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Model to copy
             */
            BaseModel(const BaseModel& other) noexcept = default;

            /**
             * @brief Move constructor
             * 
             * @param other Model to move
             */
            BaseModel(BaseModel&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            virtual ~BaseModel() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Model to copy
             * 
             * @return Reference to this model
             */
            BaseModel& operator=(const BaseModel& other) noexcept = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Model to move
             * 
             * @return Reference to this model
             */
            BaseModel& operator=(BaseModel&& other) noexcept = default;

            /**
             * @brief Constructs a deep copy of the model
             * 
             * @return Pointer to the copy
             */
            virtual std::unique_ptr<BaseModel> clone() const = 0;

            /**
             * @brief Returns the model fields
             * 
             * @return Field vector
             */
            std::unordered_map<std::string_view, std::reference_wrapper<BaseField>> getFields();

            /**
             * @brief Returns the field associated with a constant name
             * 
             * @tparam Name Field name
             * 
             * @return Field
             */
            template<tbaricault::templates::FixedString Name>
            constexpr decltype(auto) get();

            /**
             * @brief Returns a field by it's name
             * 
             * @param name Field name
             * 
             * @return Field
             * 
             * @throws std::invalid_argument If field not found
             */
            virtual BaseField& get(std::string_view name);

            /**
             * @brief Sets new value for the model
             * 
             * @param value New value
             * 
             * @throws std::invalid_argument If value is invalid
             */
            virtual void set(const std::any& value) override;

            /**
             * @brief Validates the model
             * 
             * @throws std::invalid_argument If validation error occurs
             */
            virtual void validate() const override;

            /**
             * @brief Normalizes model data
             * 
             * @return Model data as `std::any`
             */
            virtual std::any normalize() const override;

            /**
             * @brief Updates model data
             * 
             * @param data Data to update
             * 
             * @throws std::invalid_argument If value is invalid
             */
            void update(const std::unordered_map<std::string, std::any>& value);


        protected:

            /**
             * @brief Retrieves the model fields
             * 
             * @param result Vector of resulting fields
             */
            virtual void _getFields(std::unordered_map<std::string_view, std::reference_wrapper<BaseField>>& result);

            /**
             * @brief Retrieves the model data
             * 
             * @param result Map of resulting data
             */
            virtual void _normalize(std::unordered_map<std::string, std::any>& result) const;

    };

}


#include "BaseModel.tpp"
