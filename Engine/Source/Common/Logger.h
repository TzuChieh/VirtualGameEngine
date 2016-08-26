#pragma once

#include "Common/type.h"
#include "Common/logging.h"

#include <string>

namespace ve
{

enum class LogLevel : uint32;
class LogSender;

class Logger
{
public:
	static Logger defaultLogger;

	static void log(const LogSender& logSender, const LogLevel& logLevel, const std::string& message);

public:
	Logger();
	explicit Logger(const LogSender& logSender);

	void log(const LogLevel& logLevel, const std::string& message) const;
	void setLogSender(const LogSender& logSender);

private:
	LogSender m_logSender;
};

}