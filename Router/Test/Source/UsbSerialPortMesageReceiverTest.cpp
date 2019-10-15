#include "UsbSerialPortMesageReceiverTest.hpp"

namespace
{
constexpr auto queueIsEmpty = false;
}

TEST_F(UsbSerialPortMesageReceiverTest, takeMessageShouldReturnFirstMessageInQueue)
{
    addMessageToPort("firstMessage");
    addMessageToPort("secondMessage");

    _sut.receiveMessage();

    ASSERT_EQ(_sut.takeMessageFromQueue().value(), "firstMessage");
}

TEST_F(UsbSerialPortMesageReceiverTest, takeMessageShouldReturnNulloptWhenMessagesQueueIsEmpty)
{
    _sut.receiveMessage();

    ASSERT_EQ(_sut.takeMessageFromQueue(), std::nullopt);
}

TEST_F(UsbSerialPortMesageReceiverTest, takeMessageShouldRemoveFirstMessageInQueue)
{
    addMessageToPort("firstMessage");

    _sut.receiveMessage();
    _sut.takeMessageFromQueue();

    ASSERT_EQ(_sut.takeMessageFromQueue().has_value(), queueIsEmpty);
}

TEST_F(UsbSerialPortMesageReceiverTest, receiveMessageShouldNotQueueAnyMessagesIfPortIsEmpty)
{
    _sut.receiveMessage();

    ASSERT_EQ(_sut.takeMessageFromQueue().has_value(), queueIsEmpty);
}

TEST_F(UsbSerialPortMesageReceiverTest, receiveMessageShouldQueueMessageFromPort)
{
    addMessageToPort("firstMessage");

    _sut.receiveMessage();

    ASSERT_EQ(_sut.takeMessageFromQueue().has_value(), not queueIsEmpty);
}

TEST_F(UsbSerialPortMesageReceiverTest, portShouldBeEmptyAfterReceivedAllMessages)
{
    addMessageToPort("firstMessage");

    _sut.receiveMessage();
    _sut.takeMessageFromQueue();

    _sut.receiveMessage();

    ASSERT_EQ(_sut.takeMessageFromQueue().has_value(), queueIsEmpty);

}
