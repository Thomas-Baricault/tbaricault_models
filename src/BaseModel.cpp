/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <optional>
#include <stdexcept>

#include "models/BaseModel.hpp"


namespace tbaricault::models
{

    std::unordered_map<std::string_view, std::reference_wrapper<BaseField>> BaseModel::getFields()
    {
        std::unordered_map<std::string_view, std::reference_wrapper<BaseField>> result;
        this->_getFields(result);
        return (result);
    }

    BaseField& BaseModel::get(std::string_view name)
    {
        throw std::invalid_argument("unknown field '" + std::string(name) + "'");
    }

    void BaseModel::set(const std::any& value)
    {
        if (const auto* ptr = std::any_cast<std::unordered_map<std::string, std::any>>(&value))
        {
            for (auto [name, field] : this->getFields())
                if (!ptr->contains(std::string(name)))
                    field.get().set(std::nullopt);
            for (const auto& [key, value] : *ptr)
                this->get(key).set(value);
        }
        else
            throw std::invalid_argument("invalid value type");
        return;
    }

    void BaseModel::validate() const
    {
        return;
    }

    std::any BaseModel::normalize() const
    {
        std::unordered_map<std::string, std::any> result;
        this->_normalize(result);
        return (result);
    }

    void BaseModel::update(const std::unordered_map<std::string, std::any>& data)
    {
        for (const auto& [key, value] : data)
            this->get(key).set(value);
        return;
    }

    void BaseModel::_getFields(std::unordered_map<std::string_view, std::reference_wrapper<BaseField>>&)
    {
        return;
    }

    void BaseModel::_normalize(std::unordered_map<std::string, std::any>&) const
    {
        return;
    }

}
