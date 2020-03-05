#include "GrpcCommandReceiverTest.hpp"

TEST_F(GrpcCommandReceiverTest, commandsQueueShouldBeEmptyAfterClassInitialization)
{
    ASSERT_EQ(std::nullopt, _sut->takeMessageFromQueue());
}

TEST_F(GrpcCommandReceiverTest, receivedCommandShouldBeQueued)
{
    sendCommandToSut(Commands::EmptyAcknowledge{});

    ASSERT_TRUE(_sut->takeMessageFromQueue().value().Is<Commands::EmptyAcknowledge>());
}

TEST_F(GrpcCommandReceiverTest, commandsQueueShouldBeEmptyIfCommandHasBeenTaken)
{
    sendCommandToSut(Commands::EmptyAcknowledge{});

    _sut->takeMessageFromQueue().value().Is<Commands::EmptyAcknowledge>();

    ASSERT_EQ(std::nullopt, _sut->takeMessageFromQueue());
}