#pragma once

#include <gmock/gmock.h>

#include "EngineMock.hpp"
#include "SingleAxisPropulsionSystem.hpp"
#include "EngineDriverMock.hpp"
#include "MockPointer.hpp"

using namespace ::testing;

class SingleAxisPropulsionSystemTest : public Test
{
public:
    SingleAxisPropulsionSystemTest()
        : _rightEngineMock(makeMockPointer<NiceMock<EngineMock>>())
        , _leftEngineMock(makeMockPointer<NiceMock<EngineMock>>())
        , _engineDriverMock(makeMockPointer<NiceMock<EngineDriverMock>>())
        , _sut(_rightEngineMock.ownershipHandover(),
               _leftEngineMock.ownershipHandover(),
               _engineDriverMock.ownershipHandover())
    {}

    MockPointer<NiceMock<EngineMock>> _rightEngineMock;
    MockPointer<NiceMock<EngineMock>> _leftEngineMock;
    MockPointer<NiceMock<EngineDriverMock>> _engineDriverMock;
    SingleAxisPropulsionSystem _sut;
};
