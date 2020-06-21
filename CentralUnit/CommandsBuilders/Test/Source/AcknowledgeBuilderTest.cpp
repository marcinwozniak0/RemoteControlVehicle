#include <gtest/gtest.h>

#include "AcknowledgeBuilder.hpp"

TEST(ControlerCommandToRunMessageBuilderTest, shouldBuildAcknowlesgeWithGivenStatus)
{
    const auto givenStatus = Commands::Status::SUCCESS;

    const auto acknowledge = AcknowledgeBuilder{}.status(givenStatus)
                                                 .build();


    ASSERT_EQ(givenStatus, acknowledge.status());
}

TEST(ControlerCommandToRunMessageBuilderTest, shouldBuildAcknowlesgeWithAdditionalInformation)
{
    const auto givenAdditionalInformation = "additionl info";

    const auto acknowledge = AcknowledgeBuilder{}.additionalInformation(givenAdditionalInformation)
                                                 .build();


    ASSERT_EQ(givenAdditionalInformation, acknowledge.additional_info());
}

TEST(ControlerCommandToRunMessageBuilderTest, byDefaultShouldBuildAcknowlesgeWithEmptyAdditionalInfoAndSuccessStatus)
{
    const auto expectedDefaultAdditionalInfo = "";
    const auto expectedDefaultStatus = Commands::Status::SUCCESS;

    const auto acknowledge = AcknowledgeBuilder{}.build();


    ASSERT_EQ(expectedDefaultStatus, acknowledge.status());
    ASSERT_EQ(expectedDefaultAdditionalInfo, acknowledge.additional_info());
}
