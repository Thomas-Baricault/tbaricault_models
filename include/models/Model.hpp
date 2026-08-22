/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <any>
#include <cstddef>
#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>

#include <json.hpp>

#include <tbaricault/templates.hpp>

#include "BaseField.hpp"
#include "BaseModel.hpp"


namespace tbaricault::models
{

    /**
     * @brief Data model containing fields
     * 
     * @tparam Parent Model parent, use BaseModel for no parent
     * @tparam This Real model class
     * @tparam Field Model fields
     */
    template<typename Parent, typename This, typename... Fields>
    class Model
        : public Parent
    {

        public:

            /**
             * @brief Default constructor
             */
            Model();

            /**
             * @brief Copy constructor
             * 
             * @param other Model to copy
             */
            Model(const Model& other) = default;

            /**
             * @brief Move constructor
             * 
             * @param other Model to move
             */
            Model(Model&& other) noexcept = default;

            /**
             * @brief Constructs model from data
             * 
             * @param data Data to construct from
             */
            Model(const std::unordered_map<std::string, std::any>& data);

            /**
             * @brief Constructs model from JSON
             * 
             * @param json JSON to construct from
             */
            Model(const nlohmann::json& json);

            /**
             * @brief Constructs model from JSON file
             * 
             * @param path JSON file path
             */
            Model(const std::string& path);

            /**
             * @brief Destructor
             */
            virtual ~Model() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Model to copy
             * 
             * @return Reference to this model
             */
            Model& operator=(const Model& other) = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Model to move
             * 
             * @return Reference to this model
             */
            Model& operator=(Model&& other) noexcept = default;

            /**
             * @brief Constructs a deep copy of the model
             * 
             * @return Pointer to the copy
             */
            virtual std::unique_ptr<BaseModel> clone() const override;

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
            virtual BaseField& get(std::string_view name) override;

            /**
             * @brief Validates the model
             * 
             * @throws std::invalid_argument If validation error occurs
             */
            virtual void validate() const override;

            /**
             * @brief Saves the model to a JSON file
             * 
             * @param path Output file path
             * @param minified Whether the file content has to be minified
             * 
             * @throws std::invalid_argument If saving failed
             */
            void save(const std::string& path, bool minified = false) const;


        protected:

            /**
             * @brief Retrieves the model fields
             * 
             * @param result Vector of resulting fields
             */
            virtual void _getFields(std::unordered_map<std::string_view, std::reference_wrapper<BaseField>>& result) override;

            /**
             * @brief Retrieves the model data
             * 
             * @param result Map of resulting data
             */
            virtual void _normalize(std::unordered_map<std::string, std::any>& result) const override;


        private:

            /**
             * @brief Model fields
             */
            std::tuple<typename Fields::Type...> _fields;

    };

}


#include "Model.tpp"
