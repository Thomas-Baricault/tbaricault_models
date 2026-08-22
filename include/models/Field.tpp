/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <stdexcept>

#include <tbaricault/templates.hpp>

#include "Field.hpp"
#include "utils.hpp"


namespace tbaricault::models
{

    template<typename T, typename Constraints, typename Options>
    Field<T, Constraints, Options>::Field(const std::any& value)
        : BaseField()
    {
        this->set(value);
        return;
    }

    template<typename T, typename Constraints, typename Options>
    Field<T, Constraints, Options>& Field<T, Constraints, Options>::operator=(const Field& other)
    {
        if (other._value.has_value())
            this->set(other._value.value());
        else
            this->set(std::nullopt);
        return (*this);
    }

    template<typename T, typename Constraints, typename Options>
    Field<T, Constraints, Options>::operator const T&() const
    {
        return (this->get());
    }

    template<typename T, typename Constraints, typename Options>
    Field<T, Constraints, Options>::operator T&()
    {
        return (this->get());
    }

    template<typename T, typename Constraints, typename Options>
    bool Field<T, Constraints, Options>::isNull() const noexcept
    {
        return (!this->_value.has_value());
    }

    template<typename T, typename Constraints, typename Options>
    const T& Field<T, Constraints, Options>::get() const
    {
        if (!this->_value.has_value())
            throw std::runtime_error("field is null");
        return (this->_value.value());
    }

    template<typename T, typename Constraints, typename Options>
    T& Field<T, Constraints, Options>::get()
    {
        if constexpr (Options::template contains<options::Readonly>())
            throw std::runtime_error("field is readonly");
        if (!this->_value.has_value())
            throw std::runtime_error("field is null");
        return (this->_value.value());
    }

    template<typename T, typename Constraints, typename Options>
    void Field<T, Constraints, Options>::set(const std::any& value)
    {
        if constexpr (Options::template contains<options::Readonly>())
            if (this->setted)
                throw std::runtime_error("field is readonly");
        if constexpr (Options::template contains<options::Strict>())
            if (std::any_cast<std::string>(&value))
                throw std::runtime_error("cannot use string conversion on strict field");
        if (std::any_cast<std::nullopt_t>(&value))
            this->_value = std::nullopt;
        else
            this->_value = tbaricault::models::extract<T>(value);
        if (!this->_value.has_value())
        {
            if constexpr (!std::is_same_v<typename Options::DefaultType, void>)
            {
                if constexpr (std::invocable<decltype(Options::DefaultType::value)>)
                    this->_value = Options::DefaultType::value();
                else
                    this->_value = Options::DefaultType::value;
            }
        }
        this->_setted = true;
        this->validate();
        return;
    }

    template<typename T, typename Constraints, typename Options>
    void Field<T, Constraints, Options>::validate() const
    {
        if (this->_value.has_value())
        {
            Constraints::validate(this->_value.value());
            using ContainerTraits = tbaricault::templates::ContainerTraits<T>;
            if constexpr (ContainerTraits::isContainer)
            {
                using ValueTraits = FieldTraits<typename ContainerTraits::ValueType>;
                if constexpr (ValueTraits::isField)
                {
                    if constexpr (ContainerTraits::isAssociative)
                    {
                        for (const auto& [_, value] : this->_value.value())
                            value.validate();
                    }
                    else
                    {
                        for (const auto& value : this->_value.value())
                            value.validate();
                    }
                }
            }
        }
        else if constexpr (!Options::template contains<options::Optional>())
            throw std::invalid_argument("field cannot be null");
        return;
    }

    template<typename T, typename Constraints, typename Options>
    std::any Field<T, Constraints, Options>::normalize() const
    {
        if (this->_value.has_value())
            return (tbaricault::models::normalize(this->_value.value()));
        return (std::nullopt);
    }

}
