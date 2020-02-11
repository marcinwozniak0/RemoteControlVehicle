#include "GrpcCommunicationSocketTest.hpp"

namespace google::protobuf
{
    bool operator==(const HelloRequest& rhs, const HelloRequest& lhs)
    {
        return rhs.name() == lhs.name();
    }    
}

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
