#include "GrpcCommandReceiverTest.hpp"

TEST_F(GrpcCommandReceiverTest, commandToProcessShouldBeEmptyAfterClassInitialization)
{
    ASSERT_EQ(std::nullopt, _sut->takeCommandToProcess());
}

TEST_F(GrpcCommandReceiverTest, receivedCommandShouldBeStored)
{
    sendCommandToSut(Commands::Acknowledge{});

    ASSERT_TRUE(_sut->takeCommandToProcess().value().Is<Commands::Acknowledge>());

}

TEST_F(GrpcCommandReceiverTest, commandToProcessShouldBeEmptyIfCommandHasBeenTaken)
{
    sendCommandToSut(Commands::Acknowledge{});

    _sut->takeCommandToProcess().value().Is<Commands::Acknowledge>();

    ASSERT_EQ(std::nullopt, _sut->takeCommandToProcess());
}
