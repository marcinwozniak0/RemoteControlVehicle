#include "CarRental.hpp"
#include "IdDistributor.hpp"

std::optional<uint> CarRental::registerNewItem()
{
    const auto newId = _idDistributor.getFreeId();

    const auto [it, result] = _cars.emplace(newId);

    if(result)
    {
        return newId;
    }
    else
    {
        return std::nullopt;
    }
}

bool CarRental::removeItem(const uint itemId)
{
    return false;
}
