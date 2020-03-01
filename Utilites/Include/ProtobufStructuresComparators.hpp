#pragma once

#include <google/protobuf/any.pb.h>

#include <UserCommandToRun.pb.h>
#include <ControlerCommandToRun.pb.h>
#include <HelloMessages.pb.h>

#include "MapComparator.hpp"
#include "VehicleTypes.hpp"

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

inline bool operator==(const google::protobuf::Any& lhs, const google::protobuf::Any& rhs)
{
    if(lhs.Is<Messages::ControlerCommandToRun>() and rhs.Is<Messages::ControlerCommandToRun>())
    {
        Messages::ControlerCommandToRun lhsCommand;
        Messages::ControlerCommandToRun rhsCommand;

        lhs.UnpackTo(&lhsCommand);
        rhs.UnpackTo(&rhsCommand);

        return lhsCommand == rhsCommand;
    }

    return false;
}

inline bool operator==(const HelloRequest& rhs, const HelloRequest& lhs)
{
    return rhs.name() == lhs.name();
}    

}//google::protobuf
