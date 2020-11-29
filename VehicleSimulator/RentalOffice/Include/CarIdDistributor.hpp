#pragma once

#include "IdDistributor.hpp"

class CarIdDistributor : public IdDistributor
{
public:
    unsigned getFreeId() override;

private:
    unsigned _idToDistribut = 0;
};
