#include <thread>
#include <chrono>

#include <UserCommandToStart.pb.h>
#include <UserCommandToStop.pb.h>
#include <UserCommandToRun.pb.h>
#include <RegisterUserCommand.pb.h>
#include <RegisterVehicle.pb.h>
#include <Deactivate.pb.h>

#include "Logger.hpp"
#include "CommandDebuger.hpp"
#include "VehiclePoolControler.hpp"
#include "ControlerCommandToRunMessageBuilder.hpp"
#include "CommandReceiver.hpp"
#include "CommandSender.hpp"
#include "VehiclePool.hpp"
#include "Vehicle.hpp"

VehiclePoolControler::VehiclePoolControler(CommandReceiver& commandReceiver,
                                   CommandSender& commandSender,
                                   VehiclePool& vehiclePool)
    : _commandReceiver(commandReceiver)
    , _commandSender(commandSender)
    , _vehiclePool(vehiclePool)
{
    _isControlerActive = true;
}

void VehiclePoolControler::controlVehiclePool()
{
    while(_isControlerActive)
    {
        if (const auto command = _commandReceiver.takeMessageFromQueue())
        {
            handleCommand(command.value());
        }
    //TODO try to use condition variable instead of sleeping
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void VehiclePoolControler::vehiclePoolEmergencyStop()
{
    for (const auto vehicleId : _vehiclePool.getRentedVehicleIds())
    {
        auto vehicle = _vehiclePool.getVehicle(vehicleId);

        auto pinsConfiguration = vehicle.value()->getCurrentPinsConfiguration();

        clearPinsValues(pinsConfiguration);

        auto commandToSend = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(pinsConfiguration)
                                                                  .vehicleId(vehicleId)
                                                                  .build();

        sendCommand(std::move(commandToSend));
    }
}

void VehiclePoolControler::clearPinsValues(PinsConfiguration& pinsConfiguration) const
{
    for (auto& [pin, value] : pinsConfiguration)
    {
        value = 0;
    }
}

template <typename Command>
void VehiclePoolControler::sendCommand(Command&& command) const
{
    _commandSender.sendCommand(std::move(command));
}

void VehiclePoolControler::handleCommand(const google::protobuf::Any& command)
{
    INFO("Handle command : " + CommandDebuger::getCommandName(command));

    if (command.Is<Commands::RegisterUserCommand>())
    {
        handleRegisterUserCommand(command);
    }
    else if (command.Is<Commands::RegisterVehicle>())
    {
        Commands::RegisterVehicle payload;
        command.UnpackTo(&payload);

        _vehiclePool.registerVehicle(std::move(payload));
    }
    else if (command.Is<Commands::UserCommandToStart>())
    {
        Commands::UserCommandToStart payload;
        command.UnpackTo(&payload);
        auto vehicle = _vehiclePool.getVehicle(payload.vehicle_id());
        vehicle.value()->startVehicle();
    }
    else if (command.Is<Commands::UserCommandToStop>())
    {
        Commands::UserCommandToStop payload;
        command.UnpackTo(&payload);
        auto vehicle = _vehiclePool.getVehicle(payload.vehicle_id());
        vehicle.value()->stopVehicle();
    }
    else if(command.Is<Commands::UserCommandToRun>())
    {
        handleUserCommandToRun(command);
    }
    else if(command.Is<Commands::Deactivate>())
    {
        _isControlerActive = false;
    }
    else
    {
        ERROR("Handling of this command is not implemented.");
    }
    
}

void VehiclePoolControler::handleUserCommandToRun(const google::protobuf::Any& command) const
{
    Commands::UserCommandToRun payload;
    command.UnpackTo(&payload);

    const auto vehicleId = payload.vehicle_id();
    auto vehicle = _vehiclePool.getVehicle(vehicleId);

    vehicle.value()->applyNewConfiguration(payload.coordinate_system());
    const auto newPinsConfiguration = vehicle.value()->getCurrentPinsConfiguration();
    auto messageToSend = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(newPinsConfiguration)
                                                              .vehicleId(vehicleId)  
                                                              .build();

    sendCommand(std::move(messageToSend));
}

void VehiclePoolControler::handleRegisterUserCommand(const google::protobuf::Any& command) const
{
    Commands::RegisterUserCommand payload;
    command.UnpackTo(&payload);

    _vehiclePool.rentVehicle(payload.vehicle_id()); 
}

