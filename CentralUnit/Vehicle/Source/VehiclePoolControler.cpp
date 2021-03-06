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
#include "AcknowledgeBuilder.hpp"
#include "CommandReceiver.hpp"
#include "CommandSender.hpp"
#include "VehiclePool.hpp"
#include "Vehicle.hpp"

namespace
{
constexpr bool SUCCESS = true;
constexpr bool FAILED = false;

auto createAcknowledge(bool status = SUCCESS,
                       const std::string& additionalInfo = "")
{
    const auto convertedStatus = status ? Commands::Status::SUCCESS
                                        : Commands::Status::FAILED;

    return AcknowledgeBuilder{}.status(convertedStatus)
                               .additionalInformation(additionalInfo)
                               .build();
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
            auto acknowledge = handleCommand(command.value());
            _commandReceiver.setAcknowledgeToSend(std::move(acknowledge));
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
bool VehiclePoolControler::sendCommand(Command&& command) const
{
    return _commandSender.sendCommand(std::move(command));
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
        ERROR("Handling of this command is not implemented.");
        return createAcknowledge(FAILED, "Unsupported handling of command in CentralUnit");
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

    bool status = sendCommand(std::move(messageToSend));

    return createAcknowledge(status);
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
    if (auto vehicle = _vehiclePool.getVehicle(payload.vehicle_id()))
    {
        vehicle.value()->stopVehicle();
        return createAcknowledge();
    }

    return createAcknowledge(FAILED, "Vehicle with received id was not found");
}

Commands::Acknowledge VehiclePoolControler::handleUserCommandToStart(const google::protobuf::Any& command) const
{
    Commands::UserCommandToStart payload;
    command.UnpackTo(&payload);
    if (auto vehicle = _vehiclePool.getVehicle(payload.vehicle_id()))
    {
        vehicle.value()->startVehicle();
        return createAcknowledge();
    }

    return createAcknowledge(FAILED, "Vehicle with received id was not found");
}

Commands::Acknowledge VehiclePoolControler::handleRegisterVehicleCommand(const google::protobuf::Any& command) const
{
    Commands::RegisterVehicle payload;
    command.UnpackTo(&payload);

    bool isRegisterSuccess = _vehiclePool.registerVehicle(std::move(payload));
    return createAcknowledge(isRegisterSuccess);
}
