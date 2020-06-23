#include <thread>
#include <chrono>

#include "commandreceiver.hpp"
//#include "Logger.hpp"

namespace
{
std::string getStatusAsString(Commands::Status status)
{
    switch(status)
    {
        case Commands::Status::SUCCESS: return "SUCCES";
        case Commands::Status::FAILED: return "FAILED";
        default : return "UNSUPPORTED_PRINT";
    }
}
}//namespace

GrpcCommandReceiver::GrpcCommandReceiver(const std::string& portAddress)
{
    startListeningOnPort(portAddress);
}

std::optional<const google::protobuf::Any> GrpcCommandReceiver::takeCommandToProcess()
{
    if (_commandToProcess.has_value())
    {
        const auto command = _commandToProcess.value();
        _commandToProcess.reset();

        return command;
    }
    else
    {
        return {};
    }
}

void GrpcCommandReceiver::setAcknowledgeToSend(Commands::Acknowledge&& acknowledge)
{
    _acknowledgeToSend = acknowledge;
}

grpc::Status GrpcCommandReceiver::SendCommand(grpc::ServerContext* context, const google::protobuf::Any* request, Commands::Acknowledge* response)
{
    //INFO("Command received. Command will be processed");
    _commandToProcess = *request;

    waitForCommandProcessingFinish();
    //INFO("Command processing finished with status = " + getStatusAsString(_acknowledgeToSend.value().status()));

    *response = _acknowledgeToSend.value();
    _acknowledgeToSend.reset();

    return grpc::Status::OK;
}

grpc::Status GrpcCommandReceiver::SayHello(grpc::ServerContext* context, const InitCommands::HelloRequest* request, InitCommands::HelloReply* response)
{
    //INFO("Received HelloMessage from " + request->name());

    response->set_message("Successfully conected with server");

    return grpc::Status::OK;
}

void GrpcCommandReceiver::waitForCommandProcessingFinish() const
{
    using namespace std::chrono_literals;
    constexpr auto timeToAvoidHighCpuUsage = 50ms;
    while (not _acknowledgeToSend.has_value())
    {
        std::this_thread::sleep_for(timeToAvoidHighCpuUsage);
    }
}

void GrpcCommandReceiver::startListeningOnPort(const std::string& portAddress)
{
    grpc::ServerBuilder builder;
    builder.AddListeningPort(portAddress, grpc::InsecureServerCredentials());
    builder.RegisterService(this);

    _server = builder.BuildAndStart();

    //INFO("Server listening on port: " + portAddress);
}
