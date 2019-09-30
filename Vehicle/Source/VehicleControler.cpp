#include <thread>
#include <chrono>

#include <UserCommandToStart.pb.h>
#include <UserCommandToStop.pb.h>
#include <UserCommandToRun.pb.h>
#include <Deactivate.pb.h>

#include "VehicleControler.hpp"

VehicleControler::VehicleControler(MessageReceiver& messageReceiver,
                                   Vehicle& vehicle,
                                   const PinValueSetter& pinValueSetter)
    : _messageReceiver(messageReceiver)
    , _commandsQueue(_messageReceiver.shareMessagesQueue())
    , _vehicle(vehicle)
    , _pinValueSeter(pinValueSetter)
{
    _isControlerActive = true;
}

void VehicleControler::controlVehicle()
{
    //think about receiving commands
    while(_isControlerActive)
    {
        _messageReceiver.receiveMessage(); //temporary solution
        if (const auto command = getMessageToExecute())
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

std::optional<std::string> VehicleControler::getMessageToExecute()
{
    if (not _commandsQueue->empty())
    {
        const auto message = _commandsQueue->front();
        _commandsQueue->pop();
        return message;
    }
    else
    {
        return {};
    }
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
