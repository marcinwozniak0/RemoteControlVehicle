#include "CarRental.hpp"
#include "IdDistributor.hpp"

bool CarRental::registerNewItem()
{
    const auto newId = _idDistributor.getFreeId();

    const auto [it, result] = _cars.emplace(newId);

    return result;
}

bool CarRental::removeItem(const uint itemId)
{
    return false;
}
