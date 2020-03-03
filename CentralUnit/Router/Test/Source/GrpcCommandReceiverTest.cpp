#include "GrpcCommandReceiverTest.hpp"

TEST_F(GrpcCommandReceiverTest, commandsQueueShouldBeEmptyAfterClassInitialization)
{
    ASSERT_EQ(std::nullopt, _sut->takeMessageFromQueue());
}

TEST_F(GrpcCommandReceiverTest, receivedCommandShouldBeQueued)
{
    sendCommandToSut(Messages::EmptyAcknowledge{});

    ASSERT_TRUE(_sut->takeMessageFromQueue().value().Is<Messages::EmptyAcknowledge>());
}

TEST_F(GrpcCommandReceiverTest, commandsQueueShouldBeEmptyIfCommandHasBeenTaken)
{
    sendCommandToSut(Messages::EmptyAcknowledge{});

    _sut->takeMessageFromQueue().value().Is<Messages::EmptyAcknowledge>();

    ASSERT_EQ(std::nullopt, _sut->takeMessageFromQueue());
}