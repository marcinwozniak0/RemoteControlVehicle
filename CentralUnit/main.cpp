#include <google/protobuf/stubs/common.h>
#include <grpc++/grpc++.h>

#include "VehiclePoolControler.hpp"
#include "GrpcCommandSender.hpp"
#include "GrpcCommandReceiver.hpp"
#include "InternalVehiclePool.hpp"
#include "VehicleFactoryFacade.hpp"
#include "ThreeWheeledVehicleFactory.hpp"

namespace
{
constexpr auto correctrNumberOfInputArguments = 3u;
constexpr auto commandReceiverPort = 1u;
constexpr auto commandSenderPort = 2u;
constexpr auto defaultCommandReceiverPort = "5000";
constexpr auto defaultCommandSenderPort = "3000";

std::string getCommandReceiverIpAddress(int argc, char* argv[])
{
    std::string ipAddress = "127.0.0.1:";

    correctrNumberOfInputArguments == argc ? ipAddress += argv[commandReceiverPort]
                                           : ipAddress += defaultCommandReceiverPort;

    return ipAddress;
}

std::string getCommandSenderIpAddress(int argc, char* argv[])
{
    std::string ipAddress = "127.0.0.1:";

    correctrNumberOfInputArguments == argc ? ipAddress += argv[commandSenderPort]
                                           : ipAddress += defaultCommandReceiverPort;

    return ipAddress;
}
}//namespace

int main(int argc, char* argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    ThreeWheeledVehicleFactory threeWheeledVehicleFactory;

    VehicleFactoryFacade vehicleFactoryFacade(threeWheeledVehicleFactory);

    GrpcCommandReceiver commandReceiver(getCommandReceiverIpAddress(argc, argv));

    GrpcCommandSender commandSender(std::make_shared<Router::Stub>(
        grpc::CreateChannel(getCommandSenderIpAddress(argc, argv),
                            grpc::InsecureChannelCredentials())));

    InternalVehiclePool vehiclePool(vehicleFactoryFacade);

    VehiclePoolControler vehiclePoolControler(commandReceiver,
                                              commandSender,
                                              vehiclePool);

    try
    {
        vehiclePoolControler.controlVehiclePool();
    }
    catch(const std::exception& unhandledException)
    {
        std::cerr << unhandledException.what() << std::endl;
        vehiclePoolControler.vehiclePoolEmergencyStop();
    }

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
