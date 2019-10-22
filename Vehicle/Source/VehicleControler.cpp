#include <thread>
#include <chrono>

#include <UserCommandToStart.pb.h>
#include <UserCommandToStop.pb.h>
#include <UserCommandToRun.pb.h>
#include <Deactivate.pb.h>

#include "VehicleControler.hpp"
#include "ControlerCommandToRunMessageBuilder.hpp"

VehicleControler::VehicleControler(CommunicationSocket& CommunicationSocket,
                                   Vehicle& vehicle)
    : _communicationSocket(CommunicationSocket)
    , _vehicle(vehicle)
{
    _isControlerActive = true;
}

void VehicleControler::controlVehicle()
{
    while(_isControlerActive)
    {
        _communicationSocket.receiveMessage();
        if (const auto command = _communicationSocket.takeMessageFromQueue())
        {
            executeMessage(command.value());
        }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void VehicleControler::vehicleEmergencyStop()
{
    //TODO execute emergency command
}

void VehicleControler::executeMessage(const std::string& message)
{
    google::protobuf::Any incommingMessage;
    incommingMessage.ParseFromString(message);

    if (incommingMessage.Is<Messages::UserCommandToStart>())
    {
        _vehicle.startVehicle();
    }
    else if (incommingMessage.Is<Messages::UserCommandToStop>())
    {
        _vehicle.stopVehicle();
    }
    else if(incommingMessage.Is<Messages::UserCommandToRun>())
    {
        Messages::UserCommandToRun payload;
        incommingMessage.UnpackTo(&payload);

        _vehicle.applyNewConfiguration(payload.coordinate_system());

    }
    else if(incommingMessage.Is<Messages::Deactivate>())
    {
        _isControlerActive = false;
    }
}
