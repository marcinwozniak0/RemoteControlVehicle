#include <thread>
#include <chrono>

#include <UserCommandToStart.pb.h>
#include <UserCommandToStop.pb.h>
#include <UserCommandToRun.pb.h>
#include <Deactivate.pb.h>

#include "Logger.hpp"
#include "CommandDebuger.hpp"
#include "VehicleControler.hpp"
#include "ControlerCommandToRunMessageBuilder.hpp"
#include "CommunicationSocket.hpp"
#include "Vehicle.hpp"

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
        _communicationSocket.receiveCommand();
        if (const auto command = _communicationSocket.takeMessageFromQueue())
        {
            handleMessage(command.value());
        }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void VehicleControler::vehicleEmergencyStop()
{
    auto pinsConfiguration = _vehicle.getCurrentPinsConfiguration();

    clearPinsValues(pinsConfiguration);

    auto commandToSend = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(pinsConfiguration)
                                                              .build();

    sendCommand(std::move(commandToSend));
}

void VehicleControler::clearPinsValues(PinsConfiguration& pinsConfiguration) const
{
    for (auto& [pin, value] : pinsConfiguration)
    {
        value = 0;
    }
}

template <typename Command>
void VehicleControler::sendCommand(Command&& command) const
{
    _communicationSocket.sendCommand(std::move(command));
}

void VehicleControler::handleMessage(const std::string& message)
{
    google::protobuf::Any incommingMessage;
    incommingMessage.ParseFromString(message);

    INFO("Handle command : " + CommandDebuger::getCommandName(incommingMessage));

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
    else
    {
        ERROR("Handling of this command is not implemented.");
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

    sendCommand(std::move(messageToSend));
}
