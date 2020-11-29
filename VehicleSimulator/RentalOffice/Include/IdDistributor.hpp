#pragma once

class IdDistributor
{
public:
    unsigned virtual getFreeId() = 0;

    ~IdDistributor() = default;
};
