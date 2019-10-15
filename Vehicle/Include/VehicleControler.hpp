#pragma once

#include <memory>
#include <queue>
#include <optional>

#include "UsbSerialPortMesageReceiver.hpp"
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
    Vehicle& _vehicle;
    const PinValueSetter& _pinValueSeter;

    bool _isControlerActive = false;
};
