#pragma once

#include <string_view>
#include <experimental/source_location>

using source_location = std::experimental::source_location;

void DEBUG(std::string_view, const source_location& location = source_location::current());
void WARNING(std::string_view, const source_location& location = source_location::current());
void ERROR(std::string_view, const source_location& location = source_location::current());
void INFO(std::string_view, const source_location& location = source_location::current());
void clearLogs();
