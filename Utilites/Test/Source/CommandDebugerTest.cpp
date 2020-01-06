#include <gtest/gtest.h>
#include <string>

#include <Deactivate.pb.h>

#include "CommandDebuger.hpp"
#include "SerializedCommandsBuilders.hpp"

using namespace CommandDebuger;

TEST(CommandDebugerTest, getNameOfNotTopLevelCommandShouldReturnTypeOfThisCommand) 
{
    Messages::Deactivate command;
    constexpr auto expectedCommandName = "Messages.Deactivate";

    ASSERT_EQ(expectedCommandName, getCommandName(command));
}

TEST(CommandDebugerTest, getNameOfTopLevelCommandShouldReturnTypeOfInnerCommand)
{
    const auto command = UTHelpers::createSerializedDeactivateMessage();
    google::protobuf::Any incommingCommand;
    incommingCommand.ParseFromString(command);

    constexpr auto expectedCommandName = "Messages.Deactivate";

    ASSERT_EQ(expectedCommandName, getCommandName(incommingCommand));
}

TEST(CommandDebugerTest, getNameOfTopLevelCommandWithUnknownInnerCommandShouldReturnNotificationAboutUnknownCommand)
{
    const auto command = "unknowCommandInTopLevelMessage";
    google::protobuf::Any incommingCommand;
    incommingCommand.ParseFromString(command);

    constexpr auto expectedCommandName = "Unknown.Command";

    ASSERT_EQ(expectedCommandName, getCommandName(incommingCommand));
}