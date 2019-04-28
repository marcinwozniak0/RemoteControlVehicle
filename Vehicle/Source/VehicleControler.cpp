#include "VehicleControler.hpp"

VehicleControler::VehicleControler(CommandReceiver& commandReceiver,
                                   Vehicle& vehicle)
    : _commandReceiver(commandReceiver)
    , _commandsQueue(_commandReceiver.shareCommandsQueue())
    , _vehicle(vehicle)
{}

void VehicleControler::controlVehicle()
{
    //think about receiving commands
    while(true)
    {
        if (const auto command = getCommandToExecute())
        {
            executeCommand(command.value());
        }
    }
}

void VehicleControler::vehicleEmergencyStop()
{
    //execute emergency command
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
}
