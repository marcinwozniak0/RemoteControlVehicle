#include <thread>
#include <chrono>
#include <google/protobuf/any.pb.h>

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

void VehiclePoolControler::vehicleEmergencyStop(const Vehicle& vehicle, const int vehicleId)
{          
    auto pinsConfiguration = vehicle.getCurrentPinsConfiguration();

    clearPinsValues(pinsConfiguration);

    auto commandToSend = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(pinsConfiguration)
                                                              .vehicleId(vehicleId)
                                                              .build();

    sendCommand(std::move(commandToSend));
}

void VehiclePoolControler::vehiclePoolEmergencyStop()
{
    for (const auto vehicleId : _vehiclePool.getRentedVehicleIds())
    {
        if (auto vehicle = _vehiclePool.getVehicle(vehicleId))
        {
            vehicleEmergencyStop(*vehicle.value(), vehicleId);      
        }
        else
        {
            ERROR("Cannot get rented vehicle !");
        } 
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
        handleRegisterVehicleCommand(command);
    }
    else if (command.Is<Commands::UserCommandToStart>())
    {
        handleUserCommandToStart(command);
    }
    else if (command.Is<Commands::UserCommandToStop>())
    {
        handleUserCommandToStop(command);
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

void VehiclePoolControler::handleUserCommandToStop(const google::protobuf::Any& command) const
{
    Commands::UserCommandToStop payload;
    command.UnpackTo(&payload);
    auto vehicle = _vehiclePool.getVehicle(payload.vehicle_id());
    vehicle.value()->stopVehicle();
}

void VehiclePoolControler::handleUserCommandToStart(const google::protobuf::Any& command) const
{
    Commands::UserCommandToStart payload;
    command.UnpackTo(&payload);
    auto vehicle = _vehiclePool.getVehicle(payload.vehicle_id());
    vehicle.value()->startVehicle();
}

void VehiclePoolControler::handleRegisterVehicleCommand(const google::protobuf::Any& command) const
{
    Commands::RegisterVehicle payload;
    command.UnpackTo(&payload);

    _vehiclePool.registerVehicle(std::move(payload));
}