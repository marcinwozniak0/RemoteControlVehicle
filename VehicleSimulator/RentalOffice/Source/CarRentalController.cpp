#include "CarRentalController.hpp"
#include "CommandReceiver.hpp"
#include "GrpcCommandSender.hpp"

void CarRentalController::registerNewItem()
{
    _rentalOffice.registerNewItem();
    //_commandSender.sendCommand() TODO send command
}
