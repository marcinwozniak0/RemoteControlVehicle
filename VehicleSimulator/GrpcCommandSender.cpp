#include <chrono>
#include <thread>

#include <InitCommands.pb.h>
#include <Acknowledge.pb.h>

#include "GrpcCommandSender.hpp"
//#include "CommunicationSocketException.hpp"
//#include "AutoStartingTimer.hpp"
//#include "Logger.hpp"

namespace
{
using namespace std::literals::chrono_literals;
using namespace std::chrono;

constexpr auto nextReconnectionAttempt = 1s;
constexpr auto totalTimeToWaitForConnection = 60s;
constexpr auto nonZeroStatus = 1u;

template <typename Timer>
bool isWaitForConnectionTimerExpired(const Timer& waitForConnectionTimer)
{
    if (totalTimeToWaitForConnection == waitForConnectionTimer.getElapsedTime())
    {
        //ERROR("Wait for connection timer expired!. Program will be terminated");
        std::exit(nonZeroStatus);
    }

    return false;
}

//template <typename Timer>
//bool shouldWaitForConnectionEstablish(const Timer& waitForConnectionTimer)
//{
//    return waitForConnectionTimer.isTimerRunning() and not isWaitForConnectionTimerExpired(waitForConnectionTimer);
//}

void waitForNextReconnectionAttempt()
{
    std::this_thread::sleep_for(nextReconnectionAttempt);
}
}//namespace

GrpcCommandSender::GrpcCommandSender(std::shared_ptr<Router::StubInterface> stub)
    : _stub(stub)
{
   // AutoStartingTimer<seconds> waitForConnectionTimer;

   // while (shouldWaitForConnectionEstablish(waitForConnectionTimer))
   // {
     //   tryConnectWithServer(waitForConnectionTimer);
   // }
}

template <typename Timer>
void GrpcCommandSender::tryConnectWithServer(Timer& waitForConnectionTimer) const
{
    const auto connectionResult = connectWithServer();

    if (std::string::npos != connectionResult.find("RPC failed"))
    {
     //   INFO("Cannot establish connection. Next reconnection attempt will be processed");
        waitForNextReconnectionAttempt();
    }
    else
    {
        waitForConnectionTimer.stop();
    }
}

std::string GrpcCommandSender::connectWithServer() const
{
    InitCommands::HelloRequest request;
    request.set_name("VEHICLE SIMULATOR");

    InitCommands::HelloReply reply;

    grpc::ClientContext context;

   // INFO("Send HelloMessage to server");

    grpc::Status status = _stub->SayHello(&context, request, &reply);

    if (status.ok())
    {
      //  INFO("Connection with server is established. Received init message = " + reply.message());
        return reply.message();
    }
    else
    {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return "RPC failed. " + status.error_message();
    }
}

std::optional<Commands::Acknowledge> GrpcCommandSender::sendCommand(google::protobuf::Any&& commandToSend)
{
    Commands::Acknowledge acknowledge;

    grpc::ClientContext context;

    grpc::Status status = _stub->SendCommand(&context, commandToSend, &acknowledge);

    if (not status.ok())
    {
   //    ERROR("Command was not send! " + status.error_message());
        return std::nullopt;
    }

    return acknowledge;
}
