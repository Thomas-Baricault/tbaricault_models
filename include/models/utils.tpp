/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "utils.hpp"


namespace tbaricault::models
{

    template<typename T>
    T extract(const std::any& value)
    {
        if constexpr (std::is_same_v<T, nlohmann::json>)
        {
            if (const auto* ptr = std::any_cast<std::nullopt_t>(&value))
                return (nullptr);
            if (const auto* ptr = std::any_cast<bool>(&value))
                return (*ptr);
            if (const auto* ptr = std::any_cast<std::string>(&value))
                return (*ptr);
            if (const auto* ptr = std::any_cast<int>(&value))
                return (*ptr);
            if (const auto* ptr = std::any_cast<unsigned int>(&value))
                return (*ptr);
            if (const auto* ptr = std::any_cast<long>(&value))
                return (static_cast<int>(*ptr));
            if (const auto* ptr = std::any_cast<long long>(&value))
                return (static_cast<int>(*ptr));
            if (const auto* ptr = std::any_cast<unsigned long>(&value))
                return (static_cast<unsigned int>(*ptr));
            if (const auto* ptr = std::any_cast<unsigned long long>(&value))
                return (static_cast<unsigned int>(*ptr));
            if (const auto* ptr = std::any_cast<float>(&value))
                return (static_cast<double>(*ptr));
            if (const auto* ptr = std::any_cast<double>(&value))
                return (*ptr);
            if (const auto* ptr = std::any_cast<long double>(&value))
                return (static_cast<double>(*ptr));
            if (const std::vector<std::any>* ptr = std::any_cast<std::vector<std::any>>(&value))
            {
                nlohmann::json json = nlohmann::json::array();
                for (const auto& value : *ptr)
                    json.push_back(extract<nlohmann::json>(value));
                return (json);
            }
            if (const auto* ptr = std::any_cast<std::unordered_map<std::string, std::any>>(&value))
            {
                nlohmann::json json = nlohmann::json::object();
                for (const auto& [key, value] : *ptr)
                    json[key] = extract<nlohmann::json>(value);
                return (json);
            }
        }
        else
        {
            using ContainerTraits = tbaricault::templates::ContainerTraits<T>;
            if (const auto* ptr = std::any_cast<T>(&value))
                return (*ptr);
            if constexpr (std::is_base_of_v<BaseModel, T>)
                return (T{value});
            if constexpr (ContainerTraits::isContainer)
            {
                using ValueTraits = FieldTraits<typename ContainerTraits::ValueType>;
                if constexpr (ContainerTraits::isAssociative)
                {
                    if (const auto* ptr = std::any_cast<std::unordered_map<typename ContainerTraits::KeyType, std::any>>(&value))
                    {
                        T result;
                        result.reserve(ptr->size());
                        for (const auto& [key, value] : *ptr)
                        {
                            if constexpr (ValueTraits::isField || std::is_base_of_v<typename ContainerTraits::ValueType, BaseModel>)
                                result.emplace(key, value);
                            else if (const auto* p = std::any_cast<typename ContainerTraits::ValueType>(&value))
                                result.emplace(key, *p);
                            else
                                throw std::invalid_argument("invalid value type");
                        }
                        return (result);
                    }
                }
                else if (const auto* ptr = std::any_cast<std::vector<std::any>>(&value))
                {
                    T result;
                    result.reserve(ptr->size());
                    for (const auto& value : *ptr)
                    {
                        if constexpr (ValueTraits::isField || std::is_base_of_v<typename ContainerTraits::ValueType, BaseModel>)
                            result.emplace_back(value);
                        else if (const auto* p = std::any_cast<typename ContainerTraits::ValueType>(&value))
                            result.emplace_back(*p);
                        else
                            throw std::invalid_argument("invalid value type");
                    }
                    return (result);
                }
            }
            if (const auto* ptr = std::any_cast<std::string>(&value))
            {
                if constexpr (std::is_constructible_v<T, std::string>)
                    return (T{*ptr});
                return (tbaricault::uniconvert::convert<std::string, T>(*ptr));
            }
            if (const auto* ptr = std::any_cast<bool>(&value))
                return (tbaricault::uniconvert::convert<bool, T>(*ptr));
            if (const auto* ptr = std::any_cast<int>(&value))
                return (tbaricault::uniconvert::convert<int, T>(*ptr));
            if (const auto* ptr = std::any_cast<long>(&value))
                return (tbaricault::uniconvert::convert<long, T>(*ptr));
            if (const auto* ptr = std::any_cast<long long>(&value))
                return (tbaricault::uniconvert::convert<long long, T>(*ptr));
            if (const auto* ptr = std::any_cast<unsigned long>(&value))
                return (tbaricault::uniconvert::convert<unsigned long, T>(*ptr));
            if (const auto* ptr = std::any_cast<unsigned long long>(&value))
                return (tbaricault::uniconvert::convert<unsigned long long, T>(*ptr));
            if (const auto* ptr = std::any_cast<float>(&value))
                return (tbaricault::uniconvert::convert<float, T>(*ptr));
            if (const auto* ptr = std::any_cast<double>(&value))
                return (tbaricault::uniconvert::convert<double, T>(*ptr));
            if (const auto* ptr = std::any_cast<long double>(&value))
                return (tbaricault::uniconvert::convert<long double, T>(*ptr));
            if (const auto* ptr = std::any_cast<char>(&value))
                return (tbaricault::uniconvert::convert<char, T>(*ptr));
        }
        throw std::invalid_argument("invalid value type");
    }

    template<typename T>
    std::any normalize(const T& value)
    {
        if constexpr (std::is_base_of_v<BaseElement, T>)
            return (value.normalize());
        using ContainerTraits = tbaricault::templates::ContainerTraits<T>;
        if constexpr (ContainerTraits::isContainer)
        {
            if constexpr (ContainerTraits::isAssociative)
            {
                std::unordered_map<typename ContainerTraits::KeyType, std::any> result;
                result.reserve(value.size());
                for (const auto& [key, value] : value)
                    result.emplace(key, normalize(value));
                return (result);
            }
            else
            {
                std::vector<std::any> result;
                result.reserve(value.size());
                for (const auto& value : value)
                    result.emplace_back(normalize(value));
                return (result);
            }
        }
        if constexpr (std::is_same_v<T, nlohmann::json>)
        {
            if (value.is_null())
                return (std::nullopt);
            if (value.is_boolean())
                return (value.template get<bool>());
            if (value.is_string())
                return (value.template get<std::string>());
            if (value.is_number_integer())
                return (value.template get<int>());
            if (value.is_number_unsigned())
                return (value.template get<unsigned int>());
            if (value.is_number_float())
                return (value.template get<double>());
            if (value.is_array())
            {
                std::vector<std::any> result;
                if (!value.empty())
                {
                    result.reserve(value.size());
                    nlohmann::json::value_t type = value[0].type();
                    for (const auto& value : value)
                    {
                        if (value.type() != type)
                            throw std::invalid_argument("array items have different types");
                        result.push_back(normalize(value));
                        type = value.type();
                    }
                }
                return (result);
            }
            if (value.is_object())
            {
                std::unordered_map<std::string, std::any> result;
                if (!value.empty())
                {
                    result.reserve(value.size());
                    for (const auto& [key, value] : value.items())
                        result[key] = normalize(value);
                }
                return (result);
            }
            throw std::invalid_argument("unknown JSON value type");
        }
        return (value);
    }

    template<tbaricault::templates::FixedString Name>
    consteval std::size_t _fieldIndex()
    {
        return (SIZE_MAX);
    }

    template<tbaricault::templates::FixedString Name, typename First, typename... Rest>
    consteval std::size_t _fieldIndex()
    {
        if constexpr (First::name == Name)
            return (0);
        else
        {
            constexpr auto next = _fieldIndex<Name, Rest...>();
            if constexpr (next == SIZE_MAX)
                return (next);
            else
                return (1 + next);
        }
    }

}
