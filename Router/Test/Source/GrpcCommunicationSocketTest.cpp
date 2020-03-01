#include "GrpcCommunicationSocketTest.hpp"
#include "ProtobufStructuresComparators.hpp"

TEST_F(GrpcCommunicationSocketTest, shouldNotThrowInCtorWhenConnectionToServerFinishedWithSuccess)
{
    EXPECT_CALL(*_stubMock, SayHello(_, helloRequest, _)).WillOnce(Return(okStatus));
    EXPECT_NO_THROW(_sut = std::make_unique<GrpcCommunicationSocket>(_stubMock));
}

TEST_F(GrpcCommunicationSocketTest, shouldThrowInCtorWhenConnectionToServerFinishedWithFail)
{
    EXPECT_CALL(*_stubMock, SayHello(_, helloRequest, _)).WillOnce(Return(notOkStatus));
    EXPECT_THROW(_sut = std::make_unique<GrpcCommunicationSocket>(_stubMock), CommunicationSocketException);
}

TEST_F(GrpcCommunicationSocketTest, sendCommandShouldSendThisCommandThroughtGrpc)
{
    google::protobuf::Any messageToSend;
    
    EXPECT_CALL(*_stubMock, SendCommand(_, _, _)).WillOnce(Return(okStatus));
    
    _sut->sendCommand(std::move(messageToSend));
}