#include <chrono>
#include <ctime>
#include <string>

#include "Logger.hpp"

namespace
{
constexpr char debugLevel[]   = "DBG  ";
constexpr char warningLevel[] = "WRN  ";
constexpr char errorLevel[]   = "ERR  ";
constexpr char infoLevel[]    = "INF  ";
constexpr auto distanceBetweenLineNumberAndLogLevel = 4u;
const std::string logFileName = "logs.txt";


std::string getFileName(const source_location& location)
{
    const std::string filePath = location.file_name();
    const auto beginOfFileName = filePath.find_last_of('/') + 1;

    return filePath.substr(beginOfFileName);
}

void replaceLastCharacterWithSpaceCharacter(std::string& string)
{
   string.pop_back();
   string += " ";
}

std::string getLineNumber(const source_location& location)
{
   const auto lineNumber = std::to_string(location.line());

   return lineNumber + std::string(distanceBetweenLineNumberAndLogLevel - lineNumber.size(), ' ');
}

std::string getCurrentTime()
{
    const auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string timeAsString = std::ctime(&currentTime);
    replaceLastCharacterWithSpaceCharacter(timeAsString);

    return timeAsString;
}

template<const char* logLevel>
std::string buildLog(std::string_view infoToLog, const source_location& location)
{
    std::string logInfo;

    logInfo += getCurrentTime();
    logInfo += getFileName(location);
    logInfo += ":";
    logInfo += getLineNumber(location);
    logInfo += logLevel;
    logInfo += infoToLog;

    return logInfo;
}

template<const char* logLevel>
void saveLog(std::string_view infoToLog, const source_location& location)
{
    const auto logToSave = buildLog<logLevel>(infoToLog, location);
    const auto systemCommand = "echo \"" + logToSave + "\" >> " + logFileName;

    system(systemCommand.c_str());
}
}

void DEBUG(std::string_view infoToLog, const source_location& location)
{
    saveLog<debugLevel>(infoToLog, location);
}

void WARNING(std::string_view infoToLog, const source_location& location)
{
    saveLog<warningLevel>(infoToLog, location);
}

void ERROR(std::string_view infoToLog, const source_location& location)
{
    saveLog<errorLevel>(infoToLog, location);
}

void INFO(std::string_view infoToLog, const source_location& location)
{
    saveLog<infoLevel>(infoToLog, location);
}

void clearLogs()
{
    const auto commandToRemoveLogsFile = "rm -rf " + logFileName;
    system(commandToRemoveLogsFile.c_str());
}
