#include "GrpcCommandSenderTest.hpp"
#include "ProtobufStructuresComparators.hpp"

TEST_F(GrpcCommandSenderTest, sendCommandShouldSendThisCommandThroughtGrpc)
{
    google::protobuf::Any messageToSend;
    
    EXPECT_CALL(*_stubMock, SendCommand(_, _, _)).WillOnce(Return(okStatus));
    
    _sut->sendCommand(std::move(messageToSend));
}
