#include <thread>
#include <chrono>

#include "VehicleControler.hpp"
#include "Commands.hpp"

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
#include <iostream>
namespace
{
bool startsWith(const std::string& str, const std::string& pattern)
{
    return str.rfind(pattern, 0) ? false : true; //return 0 on succes
}

std::string getFieldFromCommand(const std::string& command, const uint8_t fieldNumber)
{
    uint8_t acctualPossition = 0;
    for (uint8_t i = 0; i <= fieldNumber; i++)
    {
        acctualPossition = command.find('|', acctualPossition);
        ++acctualPossition;
    }

    uint8_t endMarker = command.find('|', acctualPossition);

    return std::string(command.begin() + acctualPossition, command.begin() + endMarker);
}
}//namespace

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
    else if(startsWith(command, "DRIVE"))
    {
        //TODO jak obslugiwac i pobierac te mesgi
        //TODO musi byc w stanie != IDLE zeby przyjac takiego mesga
        const uint8_t direction = static_cast<uint8_t>(std::stoi(getFieldFromCommand(command, 0)));
        const uint8_t speed = static_cast<uint8_t>(std::stoi(getFieldFromCommand(command, 1)));

        _vehicle.run(USER_COMMAND_TO_DRIVE{direction, speed});
    }
    else if("DEACTIVATE")
    {
        _isControlerActive = false;
    }
}
