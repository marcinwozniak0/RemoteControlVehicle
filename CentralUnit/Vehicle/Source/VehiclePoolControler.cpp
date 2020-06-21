#include <thread>
#include <chrono>
#include <google/protobuf/any.pb.h>

#include <UserCommandToStart.pb.h>
#include <UserCommandToStop.pb.h>
#include <UserCommandToRun.pb.h>
#include <RegisterUserCommand.pb.h>
#include <RegisterVehicle.pb.h>
#include <Deactivate.pb.h>
#include <Acknowledge.pb.h>

#include "Logger.hpp"
#include "CommandDebuger.hpp"
#include "VehiclePoolControler.hpp"
#include "ControlerCommandToRunMessageBuilder.hpp"
#include "CommandReceiver.hpp"
#include "CommandSender.hpp"
#include "VehiclePool.hpp"
#include "Vehicle.hpp"

namespace
{
Commands::Acknowledge createAcknowledge(bool status = true,
                                        const std::string& additionalInfo = "")
{
    Commands::Acknowledge acknowledge;
    acknowledge.set_status(status ? Commands::Status::SUCCESS
                                  : Commands::Status::FAILED);
    acknowledge.set_additional_info(additionalInfo);

    return acknowledge;
}

void waitForNextCommandToProcess()
{
    using namespace std::chrono_literals;
    constexpr auto timeToWait = 50ms;
    std::this_thread::sleep_for(timeToWait);
}

}//namespace

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
        if (const auto command = _commandReceiver.takeCommandToProcess())
        {
            auto ack = handleCommand(command.value());
            _commandReceiver.setAcknowledgeToSend(std::move(ack));
        }
        else
        {
            waitForNextCommandToProcess();
        }
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

Commands::Acknowledge VehiclePoolControler::handleCommand(const google::protobuf::Any& command)
{
    INFO("Handle command : " + CommandDebuger::getCommandName(command));

    if (command.Is<Commands::RegisterUserCommand>())
    {
        return handleRegisterUserCommand(command);
    }
    else if (command.Is<Commands::RegisterVehicle>())
    {
        return handleRegisterVehicleCommand(command);
    }
    else if (command.Is<Commands::UserCommandToStart>())
    {
        return handleUserCommandToStart(command);
    }
    else if (command.Is<Commands::UserCommandToStop>())
    {
        return handleUserCommandToStop(command);
    }
    else if(command.Is<Commands::UserCommandToRun>())
    {
        return handleUserCommandToRun(command);
    }
    else if(command.Is<Commands::Deactivate>())
    {
        _isControlerActive = false;
        return createAcknowledge();
    }
    else
    {
        return createAcknowledge();//unsupported command
        ERROR("Handling of this command is not implemented.");
    }
}

Commands::Acknowledge VehiclePoolControler::handleUserCommandToRun(const google::protobuf::Any& command) const
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

    sendCommand(std::move(messageToSend)); //TODO sprawdzic wszystkie wysylanie ackow, Jaki status kiedy trzeba ustawic
    return createAcknowledge();
}
Commands::Acknowledge VehiclePoolControler::handleRegisterUserCommand(const google::protobuf::Any& command) const
{
    Commands::RegisterUserCommand payload;
    command.UnpackTo(&payload);

    bool isRentSuccess = _vehiclePool.rentVehicle(payload.vehicle_id());

    return createAcknowledge(isRentSuccess);
}

Commands::Acknowledge VehiclePoolControler::handleUserCommandToStop(const google::protobuf::Any& command) const
{
    Commands::UserCommandToStop payload;
    command.UnpackTo(&payload);
    auto vehicle = _vehiclePool.getVehicle(payload.vehicle_id());
    vehicle.value()->stopVehicle();
    return createAcknowledge();
}

Commands::Acknowledge VehiclePoolControler::handleUserCommandToStart(const google::protobuf::Any& command) const
{
    Commands::UserCommandToStart payload;
    command.UnpackTo(&payload);
    auto vehicle = _vehiclePool.getVehicle(payload.vehicle_id());
    vehicle.value()->startVehicle();
    return createAcknowledge();
}

Commands::Acknowledge VehiclePoolControler::handleRegisterVehicleCommand(const google::protobuf::Any& command) const
{
    Commands::RegisterVehicle payload;
    command.UnpackTo(&payload);

    bool isRegisterSuccess = _vehiclePool.registerVehicle(std::move(payload));
    return createAcknowledge(isRegisterSuccess);
}
