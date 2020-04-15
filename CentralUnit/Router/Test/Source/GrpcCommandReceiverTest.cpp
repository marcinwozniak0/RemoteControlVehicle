#include "GrpcCommandReceiverTest.hpp"

TEST_F(GrpcCommandReceiverTest, commandsQueueShouldBeEmptyAfterClassInitialization)
{
    ASSERT_EQ(std::nullopt, _sut->takeMessageFromQueue());
}

TEST_F(GrpcCommandReceiverTest, receivedCommandShouldBeQueued)
{
    sendCommandToSut(Commands::Acknowledge{});

    ASSERT_TRUE(_sut->takeMessageFromQueue().value().Is<Commands::Acknowledge>());
}

TEST_F(GrpcCommandReceiverTest, commandsQueueShouldBeEmptyIfCommandHasBeenTaken)
{
    sendCommandToSut(Commands::Acknowledge{});

    _sut->takeMessageFromQueue().value().Is<Commands::Acknowledge>();

    ASSERT_EQ(std::nullopt, _sut->takeMessageFromQueue());
}