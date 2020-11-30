#pragma once

#include <QObject>

#include "RentalOffice.hpp"
#include "Car.hpp"

class GrpcCommandReceiver;
class GrpcCommandSender;

class CarRentalController : public QObject
{
    Q_OBJECT
public:
    CarRentalController(GrpcCommandReceiver& commandReceiver,
                        GrpcCommandSender& commandSender,
                        RentalOffice<Car>& rentalOffice)
        : _commandReceiver(commandReceiver)
        , _commandSender(commandSender)
        , _rentalOffice(rentalOffice)
    {}

    void registerNewItem();

private:
    GrpcCommandReceiver& _commandReceiver;
    GrpcCommandSender& _commandSender;
    RentalOffice<Car>& _rentalOffice;
};
