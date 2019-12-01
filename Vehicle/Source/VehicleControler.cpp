#include <thread>
#include <chrono>

#include <UserCommandToStart.pb.h>
#include <UserCommandToStop.pb.h>
#include <UserCommandToRun.pb.h>
#include <Deactivate.pb.h>

#include "VehicleControler.hpp"
#include "ControlerCommandToRunMessageBuilder.hpp"

VehicleControler::VehicleControler(CommunicationSocket& communicationSocket,
                                   Vehicle& vehicle)
    : _communicationSocket(communicationSocket)
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
            handleMessage(command.value());
        }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void VehicleControler::vehicleEmergencyStop()
{
    //TODO execute emergency command
}

void VehicleControler::handleMessage(const std::string& message)
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
        handleUserCommandToRun(incommingMessage);
    }
    else if(incommingMessage.Is<Messages::Deactivate>())
    {
        _isControlerActive = false;
    }
}

void VehicleControler::handleUserCommandToRun(const google::protobuf::Any& command) const
{
    Messages::UserCommandToRun payload;
    command.UnpackTo(&payload);

    _vehicle.applyNewConfiguration(payload.coordinate_system());
    const auto newPinsConfiguration = _vehicle.getCurrentPinsConfiguration();
    auto messageToSend = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(newPinsConfiguration)
                                                              .build();

    std::string serializedMessage;
    messageToSend.SerializeToString(&serializedMessage);
    _communicationSocket.sendMessage(serializedMessage);
}
