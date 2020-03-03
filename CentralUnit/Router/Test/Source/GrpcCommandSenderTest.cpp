#include "GrpcCommandSenderTest.hpp"
#include "ProtobufStructuresComparators.hpp"

TEST_F(GrpcCommandSenderTest, shouldNotThrowInCtorWhenConnectionToServerFinishedWithSuccess)
{
    EXPECT_CALL(*_stubMock, SayHello(_, helloRequest, _)).WillOnce(Return(okStatus));
    EXPECT_NO_THROW(_sut = std::make_unique<GrpcCommandSender>(_stubMock));
}

TEST_F(GrpcCommandSenderTest, shouldThrowInCtorWhenConnectionToServerFinishedWithFail)
{
    EXPECT_CALL(*_stubMock, SayHello(_, helloRequest, _)).WillOnce(Return(notOkStatus));
    EXPECT_THROW(_sut = std::make_unique<GrpcCommandSender>(_stubMock), CommunicationSocketException);
}

TEST_F(GrpcCommandSenderTest, sendCommandShouldSendThisCommandThroughtGrpc)
{
    google::protobuf::Any messageToSend;
    
    EXPECT_CALL(*_stubMock, SendCommand(_, _, _)).WillOnce(Return(okStatus));
    
    _sut->sendCommand(std::move(messageToSend));
}