#pragma once

#include "MapComparator.hpp"

namespace Comparators
{
inline bool operator==(const Messages::ControlerCommandToRun& lhs, const Messages::ControlerCommandToRun& rhs)
{
    return mapComparator(lhs.pins_configuration(), rhs.pins_configuration());
}

}//CommandComparator

