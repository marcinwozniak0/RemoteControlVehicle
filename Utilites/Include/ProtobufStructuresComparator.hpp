#pragma once

#include "MapComparator.hpp"

namespace google::protobuf
{
inline bool operator==(const PinsConfiguration& lhs, const google::protobuf::Map<int, int>& rhs)
{
    return Comparators::mapComparator(lhs, rhs);
}

inline bool operator==(const google::protobuf::Map<int, int>& lhs, const google::protobuf::Map<int, int>& rhs)
{
    return Comparators::mapComparator(lhs, rhs);
}
}//google::protobuf
