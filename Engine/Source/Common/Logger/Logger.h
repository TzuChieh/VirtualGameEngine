#pragma once

#include "Common/type.h"

#include <string>

namespace xe
{

enum class LogLevel : uint32;
class LogSender;

class Logger
{
public:
	void log(const LogSender& logSender, const LogLevel& logLevel, const std::string& message) const;

public:
	static Logger engineLogger;
};

}