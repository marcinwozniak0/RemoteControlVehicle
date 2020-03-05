#include <gtest/gtest.h>
#include <string>

#include <Deactivate.pb.h>

#include "CommandDebuger.hpp"
#include "UtCommandsBuilders.hpp"

using namespace CommandDebuger;

TEST(CommandDebugerTest, getNameOfNotTopLevelCommandShouldReturnTypeOfThisCommand) 
{
    Commands::Deactivate command;
    constexpr auto expectedCommandName = "Commands.Deactivate";

    ASSERT_EQ(expectedCommandName, getCommandName(command));
}

TEST(CommandDebugerTest, getNameOfTopLevelCommandShouldReturnTypeOfInnerCommand)
{
    const auto command = UTHelpers::createDeactivateCommand();

    constexpr auto expectedCommandName = "Commands.Deactivate";

    ASSERT_EQ(expectedCommandName, getCommandName(command));
}

TEST(CommandDebugerTest, getNameOfTopLevelCommandWithUnknownInnerCommandShouldReturnNotificationAboutUnknownCommand)
{
    const auto command = "unknowCommandInTopLevelMessage";
    google::protobuf::Any incommingCommand;
    incommingCommand.ParseFromString(command);

    constexpr auto expectedCommandName = "Unknown.Command";

    ASSERT_EQ(expectedCommandName, getCommandName(incommingCommand));
}