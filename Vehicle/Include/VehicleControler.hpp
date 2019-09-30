#pragma once

#include <memory>
#include <queue>
#include <optional>

#include "MessageReceiver.hpp"
#include "Vehicle.hpp"

class PinValueSetter;

class VehicleControler
{
public:
    VehicleControler(MessageReceiver&, Vehicle&, const PinValueSetter&);

    void controlVehicle();
    void vehicleEmergencyStop();  

private:
    std::optional<std::string> getMessageToExecute();
    void executeMessage(const std::string&);

    MessageReceiver& _messageReceiver;
    std::shared_ptr<CommandsQueue> _commandsQueue;
    Vehicle& _vehicle;
    const PinValueSetter& _pinValueSeter;

    bool _isControlerActive = false;
};
