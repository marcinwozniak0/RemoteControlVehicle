#pragma once

#include <QObject>

#include "RentalOffice.hpp"
#include "Car.hpp"

using RentalItem = Car;

class CarRental : public QObject, public RentalOffice<Car>
{
    Q_OBJECT
public:
    CarRental(QObject* parent = nullptr) :
        QObject(parent)
    {}

    void registerNewItem() override {}
    void removeItem(const uint itemId) override {}
    std::vector<Car>& getAllItems() override {return cars;}

private:
    std::vector<Car> cars;
};
