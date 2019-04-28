#pragma once

#include <memory>
#include <queue>
#include <optional>

#include "CommandReceiver.hpp"

class VehicleControler
{
public:
    VehicleControler();

    void controlVehicle();
    void vehicleEmergencyStop();

private:
    std::optional<std::string> getCommandToExecute();

    std::shared_ptr<std::queue<std::string>> _commandsQueue;
    const CommandReceiver& _commandReceiver;
};
