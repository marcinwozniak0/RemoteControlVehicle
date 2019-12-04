#pragma once

#include <gmock/gmock.h>

#include "ProtobufStructuresComparator.hpp"

MATCHER_P(SerializedControlerCommandToRunMatcher, command, "")
{
  google::protobuf::Any expectedCommad;
  expectedCommad.ParseFromString(command);

  google::protobuf::Any givenCommand;
  givenCommand.ParseFromString(arg);

  if(expectedCommad.Is<Messages::ControlerCommandToRun>() and givenCommand.Is<Messages::ControlerCommandToRun>())
  {
      Messages::ControlerCommandToRun lhs;
      Messages::ControlerCommandToRun rhs;

      expectedCommad.UnpackTo(&lhs);
      givenCommand.UnpackTo(&rhs);

      return lhs.pins_configuration() == rhs.pins_configuration();
  }

  return false;
}

