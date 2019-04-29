#pragma once

struct USER_COMMAND_TO_DRIVE
{
    USER_COMMAND_TO_DRIVE(const bool direction, const uint8_t speed)
        : _direction(direction)
        , _speed(speed)
    {}

    const bool _direction;
    const uint8_t _speed;
};
