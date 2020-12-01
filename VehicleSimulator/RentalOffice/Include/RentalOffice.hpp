#pragma once

#include <set>
#include <optional>

template <typename Item>
class RentalOffice
{
public:
    virtual std::optional<uint> registerNewItem() = 0;
    virtual bool removeItem(const uint itemId) = 0;
    virtual std::set<Item>& getAllItems() = 0;

    ~RentalOffice() = default;
};
