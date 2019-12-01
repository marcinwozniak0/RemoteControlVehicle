#include "TcpCommunicationSocketTest.hpp"

namespace
{
constexpr auto queueIsEmpty = false;
}

TEST_F(DISABLED_TcpCommunicationSocketTest, takeMessageShouldReturnFirstMessageInQueue)
{
    addMessageToPort("firstMessage");
    addMessageToPort("secondMessage");

    _sut->receiveCommand();

    ASSERT_EQ(_sut->takeMessageFromQueue().value(), "firstMessage");
}

TEST_F(DISABLED_TcpCommunicationSocketTest, takeMessageShouldReturnNulloptWhenMessagesQueueIsEmpty)
{
    _sut->receiveCommand();

    ASSERT_EQ(_sut->takeMessageFromQueue(), std::nullopt);
}

TEST_F(DISABLED_TcpCommunicationSocketTest, takeMessageShouldRemoveFirstMessageInQueue)
{
    addMessageToPort("firstMessage");

    _sut->receiveCommand();
    _sut->takeMessageFromQueue();

    ASSERT_EQ(_sut->takeMessageFromQueue().has_value(), queueIsEmpty);
}

TEST_F(DISABLED_TcpCommunicationSocketTest, receiveCommandShouldNotQueueAnyMessagesIfPortIsEmpty)
{
    _sut->receiveCommand();

    ASSERT_EQ(_sut->takeMessageFromQueue().has_value(), queueIsEmpty);
}

TEST_F(DISABLED_TcpCommunicationSocketTest, receiveCommandShouldQueueMessageFromPort)
{
    addMessageToPort("firstMessage");

    _sut->receiveCommand();

    ASSERT_EQ(_sut->takeMessageFromQueue().has_value(), not queueIsEmpty);
}

TEST_F(DISABLED_TcpCommunicationSocketTest, portShouldBeEmptyAfterReceivedAllMessages)
{
    addMessageToPort("firstMessage");

    _sut->receiveCommand();
    _sut->takeMessageFromQueue();

    _sut->receiveCommand();

    ASSERT_EQ(_sut->takeMessageFromQueue().has_value(), queueIsEmpty);

}
