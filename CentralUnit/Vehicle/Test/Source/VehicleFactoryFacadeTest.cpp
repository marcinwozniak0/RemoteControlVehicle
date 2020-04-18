#include <VehicleType.pb.h>
#include <RegisterVehicle.pb.h>

#include "ProtobufStructuresComparators.hpp"
#include "VehicleFactoryFacadeTest.hpp"

namespace
{
constexpr auto vehicleId = 5u;

Commands::RegisterVehicle createRegisterVehicleCommandWithVehicleType()
{
    Commands::RegisterVehicle registerVehicleCommand {};
    registerVehicleCommand.set_vehicle_id(vehicleId);
    registerVehicleCommand.set_vehicle_type(Commands::VehicleType::THREE_WHEELED);

    ThreeWheeledVehicleConfiguration vehicleConfiguration {};
    google::protobuf::Any packedVehicleConfiguration {};
    packedVehicleConfiguration.PackFrom(vehicleConfiguration);

    *registerVehicleCommand.mutable_vehicle_configuration() = packedVehicleConfiguration;

    return registerVehicleCommand;
}
}

TEST_F(VehicleFactoryFacadeTest, shouldCallThreeWheeledVehicleFactoryForThreeWheeledVehicleType)
{
    auto x = createRegisterVehicleCommandWithVehicleType();
    EXPECT_CALL(_threeWheeledVehicleFactory, create(std::move(x)));

    ASSERT_NO_THROW(_sut.create(std::move(x)));
}
