#pragma once

#include <google/protobuf/any.pb.h>

#include <UserCommandToRun.pb.h>
#include <ControlerCommandToRun.pb.h>
#include <InitCommands.pb.h>
#include <RegisterVehicle.pb.h>

#include "MapComparator.hpp"
#include "VehicleTypes.hpp"

namespace Commands
{
inline bool operator==(const Commands::CoordinateSystem& lhs, const Commands::CoordinateSystem& rhs)
{
    return lhs.x_coordinate() == rhs.x_coordinate()
            and lhs.y_coordinate() == rhs.y_coordinate();
}

inline bool operator==(const Commands::ControlerCommandToRun& lhs, const Commands::ControlerCommandToRun& rhs)
{
    return Comparators::mapComparator(lhs.pins_configuration(), rhs.pins_configuration());
}

inline bool operator==(const Commands::RegisterVehicle& lhs, const Commands::RegisterVehicle& rhs)
{
    return lhs.vehicle_id() == rhs.vehicle_id();
}

}//Commands

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
    if(lhs.Is<Commands::ControlerCommandToRun>() and rhs.Is<Commands::ControlerCommandToRun>())
    {
        Commands::ControlerCommandToRun lhsCommand;
        Commands::ControlerCommandToRun rhsCommand;

        lhs.UnpackTo(&lhsCommand);
        rhs.UnpackTo(&rhsCommand);

        return lhsCommand == rhsCommand;
    }

    return false;
}

inline bool operator==(const InitCommands::HelloRequest& rhs, const InitCommands::HelloRequest& lhs)
{
    return rhs.name() == lhs.name();
}    

}//google::protobuf
