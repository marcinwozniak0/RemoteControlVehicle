#pragma once

#include <vector>

template <typename Item>
class RentalOffice
{
public:
    virtual void registerNewItem() = 0;
    virtual void removeItem(const uint itemId) = 0;
    virtual std::vector<Item>& getAllItems() = 0;

    ~RentalOffice() = default;
};
