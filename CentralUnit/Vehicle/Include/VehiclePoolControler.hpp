#pragma once

#include <optional>

#include "VehicleTypes.hpp"

namespace google::protobuf
{
class Any;
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
    void handleCommand(const google::protobuf::Any&);
    void handleUserCommandToRun(const google::protobuf::Any&) const;
    void handleRegisterUserCommand(const google::protobuf::Any&) const;
    void handleUserCommandToStop(const google::protobuf::Any&) const;
    void handleUserCommandToStart(const google::protobuf::Any&) const;
    void handleRegisterVehicleCommand(const google::protobuf::Any&) const;
    template <typename Command> void sendCommand(Command&&) const;
    void clearPinsValues(PinsConfiguration&) const;
    void vehicleEmergencyStop(const Vehicle&, int vehicleId);

    CommandReceiver& _commandReceiver;
    CommandSender& _commandSender;
    VehiclePool& _vehiclePool;

    bool _isControlerActive = false;
};
