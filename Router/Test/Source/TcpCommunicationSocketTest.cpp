#include "TcpCommunicationSocketTest.hpp"

namespace
{
constexpr auto queueIsEmpty = false;
}

TEST_F(TcpCommunicationSocketTest, takeMessageShouldReturnFirstMessageInQueue)
{
    addMessageToPort("firstMessage");
    addMessageToPort("secondMessage");

    _sut.receiveMessage();

    ASSERT_EQ(_sut.takeMessageFromQueue().value(), "firstMessage");
}

TEST_F(TcpCommunicationSocketTest, takeMessageShouldReturnNulloptWhenMessagesQueueIsEmpty)
{
    _sut.receiveMessage();

    ASSERT_EQ(_sut.takeMessageFromQueue(), std::nullopt);
}

TEST_F(TcpCommunicationSocketTest, takeMessageShouldRemoveFirstMessageInQueue)
{
    addMessageToPort("firstMessage");

    _sut.receiveMessage();
    _sut.takeMessageFromQueue();

    ASSERT_EQ(_sut.takeMessageFromQueue().has_value(), queueIsEmpty);
}

TEST_F(TcpCommunicationSocketTest, receiveMessageShouldNotQueueAnyMessagesIfPortIsEmpty)
{
    _sut.receiveMessage();

    ASSERT_EQ(_sut.takeMessageFromQueue().has_value(), queueIsEmpty);
}

TEST_F(TcpCommunicationSocketTest, receiveMessageShouldQueueMessageFromPort)
{
    addMessageToPort("firstMessage");

    _sut.receiveMessage();

    ASSERT_EQ(_sut.takeMessageFromQueue().has_value(), not queueIsEmpty);
}

TEST_F(TcpCommunicationSocketTest, portShouldBeEmptyAfterReceivedAllMessages)
{
    addMessageToPort("firstMessage");

    _sut.receiveMessage();
    _sut.takeMessageFromQueue();

    _sut.receiveMessage();

    ASSERT_EQ(_sut.takeMessageFromQueue().has_value(), queueIsEmpty);

}
