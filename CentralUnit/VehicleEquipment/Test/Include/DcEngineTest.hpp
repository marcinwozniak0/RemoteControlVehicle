#pragma once

#include <gtest/gtest.h>

#include "DcEngine.hpp"

using namespace ::testing;

class DcEngineTest : public Test
{
public:
    DcEngineTest();
    DcEngine _sut;
};
