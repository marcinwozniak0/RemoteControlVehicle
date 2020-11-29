#pragma once

struct Car
{
    Car(const uint id) : _id(id)
    {}

    bool operator< (const Car& car) const
    {
        return _id < car._id;
    }

    const uint _id;
};
