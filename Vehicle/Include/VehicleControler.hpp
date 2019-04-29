#pragma once

#include <memory>
#include <queue>
#include <optional>

#include "CommandReceiver.hpp"
#include "Vehicle.hpp"

class VehicleControler
{
public:
    VehicleControler(CommandReceiver&, Vehicle&);

    void controlVehicle();
    void vehicleEmergencyStop();  

private:
    std::optional<std::string> getCommandToExecute();
    void executeCommand(const std::string&);

    CommandReceiver& _commandReceiver;
    std::shared_ptr<std::queue<std::string>> _commandsQueue;
    Vehicle& _vehicle;
    bool _isControlerActive = false;
};
