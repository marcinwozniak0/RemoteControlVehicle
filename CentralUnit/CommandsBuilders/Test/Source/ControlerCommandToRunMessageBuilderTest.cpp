#include <gtest/gtest.h>

#include <ControlerCommandToRun.pb.h>

#include "VehicleTypes.hpp"
#include "ControlerCommandToRunMessageBuilder.hpp"
#include "ProtobufStructuresComparators.hpp"

TEST(ControlerCommandToRunMessageBuilderTest, shouldBuildMessageWithCorrectPinsConfiguration)
{
    const PinsConfiguration pinsConfiguration = {{20, 1}, {13, 0}, {10, 123}};
    const auto message = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(pinsConfiguration)
                             .build();

    Commands::ControlerCommandToRun payload;
    message.UnpackTo(&payload);

    ASSERT_EQ(pinsConfiguration, payload.pins_configuration());
}

TEST(ControlerCommandToRunMessageBuilderTest, shouldBuildMessageWithEmptyPinsConfiguration)
{
    const auto message = ControlerCommandToRunMessageBuilder{}.build();

    Commands::ControlerCommandToRun payload;
    message.UnpackTo(&payload);

    const PinsConfiguration emptyPinsConfiguration = {};

    ASSERT_EQ(emptyPinsConfiguration, payload.pins_configuration());
}