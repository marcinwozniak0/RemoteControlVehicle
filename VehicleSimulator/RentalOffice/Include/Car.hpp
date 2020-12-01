#pragma once

#include "RentalItemStatus.hpp"

struct Car
{
    Car(const uint id)
        : _id(id)
        , _status(RentalItemStatus::Free)
    {}

    bool operator< (const Car& car) const
    {
        return _id < car._id;
    }

    const uint _id;
    RentalItemStatus _status;
};
