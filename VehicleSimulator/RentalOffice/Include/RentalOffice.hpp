#pragma once

#include <set>

template <typename Item>
class RentalOffice
{
public:
    virtual bool registerNewItem() = 0;
    virtual bool removeItem(const uint itemId) = 0;
    virtual std::set<Item>& getAllItems() = 0;

    ~RentalOffice() = default;
};
