#include <thread>
#include <chrono>

#include "VehicleControler.hpp"

VehicleControler::VehicleControler(CommandReceiver& commandReceiver,
                                   Vehicle& vehicle)
    : _commandReceiver(commandReceiver)
    , _commandsQueue(_commandReceiver.shareCommandsQueue())
    , _vehicle(vehicle)
{
    _isControlerActive = true;
}

void VehicleControler::controlVehicle()
{
    //think about receiving commands
    while(_isControlerActive)
    {
        if (const auto command = getCommandToExecute())
        {
            executeCommand(command.value());
        }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void VehicleControler::vehicleEmergencyStop()
{
    //TODO execute emergency command
}

std::optional<std::string> VehicleControler::getCommandToExecute()
{
    if (not _commandsQueue->empty())
    {
        const auto command = _commandsQueue->front();
        _commandsQueue->pop();

        return command;
    }
    else
    {
        return {};
    }
}

void VehicleControler::executeCommand(const std::string& command)
{
    if("START" == command)
    {
        _vehicle.startVehicle();
    }
    else if("STOP" == command)
    {
        _vehicle.stopVehicle();
    }
    else if("DEACTIVATE")
    {
        _isControlerActive = false;
    }
}
