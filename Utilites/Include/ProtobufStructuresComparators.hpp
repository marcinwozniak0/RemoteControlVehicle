#pragma once

#include <UserCommandToRun.pb.h>
#include <ControlerCommandToRun.pb.h>

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

namespace Messages
{
inline bool operator==(const Messages::CoordinateSystem& lhs, const Messages::CoordinateSystem& rhs)
{
    return lhs.x_coordinate() == rhs.x_coordinate()
            and lhs.y_coordinate() == rhs.y_coordinate();
}

inline bool operator==(const Messages::ControlerCommandToRun& lhs, const Messages::ControlerCommandToRun& rhs)
{
    return Comparators::mapComparator(lhs.pins_configuration(), rhs.pins_configuration());
}
}//Messages
