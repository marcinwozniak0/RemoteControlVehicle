#pragma once

#include <optional>

#include "VehicleTypes.hpp"

namespace google::protobuf
{
class Any;
}

namespace Commands
{
class Acknowledge;
}

class CommandReceiver;
class CommandSender;
class VehiclePool;
class Vehicle;

class VehiclePoolControler
{
public:
    VehiclePoolControler(CommandReceiver&, CommandSender&, VehiclePool&);

    void controlVehiclePool();
    void vehiclePoolEmergencyStop();  

private:
    std::optional<std::string> getMessageToExecute();
    Commands::Acknowledge handleCommand(const google::protobuf::Any&); //TODO tutaj bool, i gdzie indziej rzutowania na status
    Commands::Acknowledge handleUserCommandToRun(const google::protobuf::Any&) const;
    Commands::Acknowledge handleRegisterUserCommand(const google::protobuf::Any&) const;
    Commands::Acknowledge handleUserCommandToStop(const google::protobuf::Any&) const;
    Commands::Acknowledge handleUserCommandToStart(const google::protobuf::Any&) const;
    Commands::Acknowledge handleRegisterVehicleCommand(const google::protobuf::Any&) const;
    template <typename Command> bool sendCommand(Command&&) const;
    void clearPinsValues(PinsConfiguration&) const;
    void vehicleEmergencyStop(const Vehicle&, int vehicleId);

    CommandReceiver& _commandReceiver;
    CommandSender& _commandSender;
    VehiclePool& _vehiclePool;

    bool _isControlerActive = false;
};
