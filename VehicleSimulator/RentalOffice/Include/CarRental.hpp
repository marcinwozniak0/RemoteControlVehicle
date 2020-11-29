#pragma once

#include <QObject>

#include "RentalOffice.hpp"

using RentalItem = int;

class CarRental : public QObject, public RentalOffice<RentalItem>
{
    Q_OBJECT
public:
    CarRental(QObject* parent = nullptr) :
        QObject(parent)
    {}

    void registerNewItem() override {}
    void removeItem(const uint itemId) override {}
    std::vector<RentalItem>& getAllItems() override {return cars;}

private:
    std::vector<RentalItem> cars;
};
