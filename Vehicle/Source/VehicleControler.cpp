#include "VehicleControler.hpp"

VehicleControler::VehicleControler()
    : _commandsQueue(std::make_shared<std::queue<std::string>>())
    , _commandReceiver(_commandsQueue)
{}

void VehicleControler::controlVehicle()
{
    //think about receiving commands
    while(true)
    {
        if (const auto command = getCommandToExecute())
        {

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
        const auto& command = _commandsQueue->front();
        _commandsQueue->pop();
        return command;
    }
    else
    {
        return {};
    }
}
