#pragma once

#include <google/protobuf/any.pb.h>

#include "VehicleTypes.hpp"

class CommandReceiver;
class CommandSender;
class Vehicle;

class VehicleControler
{
public:
    VehicleControler(CommandReceiver&, CommandSender&, Vehicle&);

    void controlVehicle();
    void vehicleEmergencyStop();  

private:
    std::optional<std::string> getMessageToExecute();
    void handleCommand(const google::protobuf::Any&);
    void handleUserCommandToRun(const google::protobuf::Any&) const;
    template <typename Command> void sendCommand(Command&&) const;
    void clearPinsValues(PinsConfiguration&) const;

    CommandReceiver& _commandReceiver;
    CommandSender& _commandSender;
    Vehicle& _vehicle;

    bool _isControlerActive = false;
};
