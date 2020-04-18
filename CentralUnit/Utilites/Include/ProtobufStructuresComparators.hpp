#pragma once

#include <google/protobuf/any.pb.h>

#include <UserCommandToRun.pb.h>
#include <ControlerCommandToRun.pb.h>
#include <InitCommands.pb.h>
#include <RegisterVehicle.pb.h>
#include <ThreeWheeledVehicleConfiguration.pb.h>

#include "MapComparator.hpp"
#include "VehicleTypes.hpp"

namespace google::protobuf
{
inline bool operator==(const google::protobuf::Any& lhs, const google::protobuf::Any& rhs); 
}

namespace Commands
{
inline bool operator==(const Commands::CoordinateSystem& lhs, const Commands::CoordinateSystem& rhs)
{
    return lhs.x_coordinate() == rhs.x_coordinate()
            and lhs.y_coordinate() == rhs.y_coordinate();
}

inline bool operator==(const Commands::ControlerCommandToRun& lhs, const Commands::ControlerCommandToRun& rhs)
{
    return Comparators::mapComparator(lhs.pins_configuration(), rhs.pins_configuration()) and
        lhs.vehicle_id() == lhs.vehicle_id();
}

inline bool operator==(const Commands::RegisterVehicle& lhs, const Commands::RegisterVehicle& rhs)
{
    return lhs.vehicle_id() == rhs.vehicle_id() and
           lhs.vehicle_type() == lhs.vehicle_type() and
           lhs.vehicle_configuration() == lhs.vehicle_configuration();
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

inline bool operator==(const ThreeWheeledVehicleConfiguration& lhs, const ThreeWheeledVehicleConfiguration& rhs)
{
    return lhs.first_engine_first_output() == rhs.first_engine_first_output() and
           lhs.first_engine_second_output() == rhs.first_engine_second_output() and
           lhs.first_engine_pwm() == rhs.first_engine_pwm() and
           lhs.second_engine_first_output() == rhs.second_engine_first_output() and
           lhs.second_engine_second_output() == rhs.second_engine_second_output() and
           lhs.second_engine_pwm() == rhs.second_engine_pwm() and
           lhs.steering_wheel_pwm_range() == rhs.steering_wheel_pwm_range() and
           lhs.engines_pwm_range() == rhs.engines_pwm_range();
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
    else if(lhs.Is<ThreeWheeledVehicleConfiguration>() and rhs.Is<ThreeWheeledVehicleConfiguration>())
    {
        ThreeWheeledVehicleConfiguration lhsConfiguration;
        ThreeWheeledVehicleConfiguration rhsConfiguration;

        lhs.UnpackTo(&lhsConfiguration);
        rhs.UnpackTo(&rhsConfiguration);

        return lhsConfiguration == rhsConfiguration;
    }

    return false;
}

inline bool operator==(const InitCommands::HelloRequest& rhs, const InitCommands::HelloRequest& lhs)
{
    return rhs.name() == lhs.name();
}    

}//google::protobuf
