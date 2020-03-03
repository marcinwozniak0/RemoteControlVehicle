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
#include "CommandReceiver.hpp"
#include "CommandSender.hpp"
#include "Vehicle.hpp"

VehicleControler::VehicleControler(CommandReceiver& commandReceiver,
                                   CommandSender& commandSender,
                                   Vehicle& vehicle)
    : _commandReceiver(commandReceiver)
    , _commandSender(commandSender)
    , _vehicle(vehicle)
{
    _isControlerActive = true;
}

void VehicleControler::controlVehicle()
{
    while(_isControlerActive)
    {
        if (const auto command = _commandReceiver.takeMessageFromQueue())
        {
            handleCommand(command.value());
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
    _commandSender.sendCommand(std::move(command));
}

void VehicleControler::handleCommand(const google::protobuf::Any& command)
{
    INFO("Handle command : " + CommandDebuger::getCommandName(command));

    if (command.Is<Messages::UserCommandToStart>())
    {
        _vehicle.startVehicle();
    }
    else if (command.Is<Messages::UserCommandToStop>())
    {
        _vehicle.stopVehicle();
    }
    else if(command.Is<Messages::UserCommandToRun>())
    {
        handleUserCommandToRun(command);
    }
    else if(command.Is<Messages::Deactivate>())
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
