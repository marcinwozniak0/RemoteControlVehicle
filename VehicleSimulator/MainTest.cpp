#include <gtest/gtest.h>
#include <google/protobuf/stubs/common.h>

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    const auto result = RUN_ALL_TESTS();

    google::protobuf::ShutdownProtobufLibrary();

    return result;
}
