#include "CarIdDistributor.hpp"

unsigned CarIdDistributor::getFreeId()
{
    return _idToDistribut++;
}
