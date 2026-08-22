/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <fstream>

#include "Model.hpp"
#include "utils.hpp"


namespace tbaricault::models
{

    template<typename Parent, typename This, typename... Fields>
    Model<Parent, This, Fields...>::Model()
        : Parent()
    {
        this->set(std::unordered_map<std::string, std::any>{});
        return;
    }

    template<typename Parent, typename This, typename... Fields>
    Model<Parent, This, Fields...>::Model(const std::unordered_map<std::string, std::any>& data)
        : Parent()
    {
        this->set(data);
        return;
    }

    template<typename Parent, typename This, typename... Fields>
    Model<Parent, This, Fields...>::Model(const nlohmann::json& json)
        : Parent()
    {
        if (!json.is_object())
            throw std::runtime_error("JSON content has to be an object");
        this->set(normalize(json));
        return;
    }

    template<typename Parent, typename This, typename... Fields>
    Model<Parent, This, Fields...>::Model(const std::string& path)
        : Parent()
    {
        std::ifstream file(path);
        if (!file)
            throw std::runtime_error("unable to read file '" + path + "'");
        nlohmann::json json;
        file >> json;
        this->set(normalize(json));
        return;
    }

    template<typename Parent, typename This, typename... Fields>
    std::unique_ptr<BaseModel> Model<Parent, This, Fields...>::clone() const
    {
        return (std::make_unique<This>(*static_cast<const This*>(this)));
    }

    template<typename Parent, typename This, typename... Fields>
    template<tbaricault::templates::FixedString Name>
    constexpr decltype(auto) Model<Parent, This, Fields...>::get()
    {
        constexpr auto index = _fieldIndex<Name, Fields...>();
        if constexpr (index == SIZE_MAX)
            return (Parent::template get<Name>());
        else
            return (std::get<index>(this->_fields));
    }

    template<typename Parent, typename This, typename... Fields>
    BaseField& Model<Parent, This, Fields...>::get(std::string_view name)
    {
        BaseField* ptr = nullptr;
        ([&] {
            if (Fields::name == name)
                ptr = &std::get<_fieldIndex<Fields::name, Fields...>()>(_fields);
        }(), ...);
        if (ptr)
            return (*ptr);
        return (Parent::get(name));
    }

    template<typename Parent, typename This, typename... Fields>
    void Model<Parent, This, Fields...>::validate() const
    {
        (std::get<typename Fields::Type>(_fields).validate(), ...);
        Parent::validate();
        return;
    }

    template<typename Parent, typename This, typename... Fields>
    void Model<Parent, This, Fields...>::save(const std::string& path, bool minified) const
    {
        std::ofstream file(path);
        if (!file)
            throw std::invalid_argument("unable to open file '" + path + "'");
        auto json = tbaricault::models::extract<nlohmann::json>(this->normalize());
        if (minified)
            file << json;
        else
            file << json.dump(4);
        return;
    }

    template<typename Parent, typename This, typename... Fields>
    void Model<Parent, This, Fields...>::_getFields(std::unordered_map<std::string_view, std::reference_wrapper<BaseField>>& result)
    {
        Parent::_getFields(result);
        (result.emplace(Fields::name, static_cast<BaseField&>(std::get<typename Fields::Type>(_fields))), ...);
        return;
    }

    template<typename Parent, typename This, typename... Fields>
    void Model<Parent, This, Fields...>::_normalize(std::unordered_map<std::string, std::any>& result) const
    {
        Parent::_normalize(result);
        ([&] {
            const auto& field = std::get<typename Fields::Type>(_fields);
            result[std::string(Fields::name)] = field.normalize();
        }(), ...);
        return;
    }

}
