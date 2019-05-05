#pragma once

#include <gmock/gmock.h>

#include "PinValueSetter.hpp"

class PinValueSetterMock : public PinValueSetter
{
public:
    MOCK_CONST_METHOD2(setValue, void (uint8_t pin, uint8_t));
};
