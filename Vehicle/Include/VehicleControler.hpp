#pragma once

#include <memory>
#include <queue>
#include <optional>

#include "MessageReceiver.hpp"
#include "Vehicle.hpp"

class VehicleControler
{
public:
    VehicleControler(MessageReceiver&, Vehicle&);

    void controlVehicle();
    void vehicleEmergencyStop();  

private:
    std::optional<std::string> getMessageToExecute();
    void executeMessage(const std::string&);

    MessageReceiver& _messageReceiver;
    std::shared_ptr<CommandsQueue> _commandsQueue;
    Vehicle& _vehicle;
    bool _isControlerActive = false;
};
