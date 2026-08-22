/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include "models/BaseElement.hpp"


namespace tbaricault::models
{

    BaseElement& BaseElement::operator=(const std::any& other)
    {
        this->set(other);
        return (*this);
    }

}
