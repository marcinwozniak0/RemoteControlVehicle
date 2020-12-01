#pragma once

#include <QObject>

#include "RentalOffice.hpp"
#include "Car.hpp"

class IdDistributor;

using RentalItem = Car;

class CarRental : public QObject, public RentalOffice<Car>
{
    Q_OBJECT
public:
    CarRental(IdDistributor& idDistributor, QObject* parent = nullptr)
        : QObject(parent)
        , _idDistributor(idDistributor)
    {}

    std::optional<uint> registerNewItem() override;
    bool removeItem(const uint itemId) override;
    std::set<Car>& getAllItems() override {return _cars;}

private:
    std::set<Car> _cars;
    IdDistributor& _idDistributor;
};
