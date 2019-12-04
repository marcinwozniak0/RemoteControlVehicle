#pragma once

#include <gmock/gmock.h>

MATCHER_P(SerializedControlerCommandToRunMatcher, command, "")
{
  google::protobuf::Any commandToMatch;
  commandToMatch.ParseFromString(command);

  google::protobuf::Any commandInArgument;
  commandInArgument.ParseFromString(arg);

  if(commandToMatch.Is<Messages::ControlerCommandToRun>() and commandInArgument.Is<Messages::ControlerCommandToRun>())
  {
      Messages::ControlerCommandToRun x;
      Messages::ControlerCommandToRun y;

      commandToMatch.UnpackTo(&x);
      commandInArgument.UnpackTo(&y);

      return std::is_permutation(x.pins_configuration().begin(),
                                 x.pins_configuration().end(),
                                 y.pins_configuration().begin(),
                                 [](const auto a, const auto b){return a.first == b.first;});
  }

  return false;
}

