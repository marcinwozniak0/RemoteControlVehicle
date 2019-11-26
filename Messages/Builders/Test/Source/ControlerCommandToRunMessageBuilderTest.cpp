#include <gtest/gtest.h>

#include <ControlerCommandToRun.pb.h>

#include "VehicleTypes.hpp"
#include "ControlerCommandToRunMessageBuilder.hpp"

namespace google::protobuf
{
inline bool operator==(const PinsConfiguration& lhs, const google::protobuf::Map<int, int>& rhs)
{

    return lhs.size() == rhs.size() &&
           std::is_permutation(lhs.begin(),
                               lhs.end(),
                               rhs.begin(),
                               [](const auto a, const auto b){return a.first == b.first;});
}
}

TEST(ControlerCommandToRunMessageBuilderTest, shouldBuildMessageWithCorrectPinsConfiguration)
{
    const PinsConfiguration pinsConfiguration = {{20, 1}, {13, 0}, {10, 123}};
    const auto message = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(pinsConfiguration)
                             .build();

    Messages::ControlerCommandToRun payload;
    message.UnpackTo(&payload);

    ASSERT_EQ(pinsConfiguration, payload.pins_configuration());
}

TEST(ControlerCommandToRunMessageBuilderTest, shouldBuildMessageWithEmptyPinsConfiguration)
{
    const auto message = ControlerCommandToRunMessageBuilder{}.build();

    Messages::ControlerCommandToRun payload;
    message.UnpackTo(&payload);

    const PinsConfiguration emptyPinsConfiguration = {};
    ASSERT_EQ(emptyPinsConfiguration, payload.pins_configuration());
}
