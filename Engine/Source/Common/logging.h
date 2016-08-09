#pragma once

// FIXME:
#define ENGINE_ENABLE_LOGGING

#include "type.h"

#include <string>

namespace xe
{

enum class LogLevel : uint32
{
	NOTE_MESSAGE,
	NOTE_WARNING,
	RECOVERABLE_ERROR,
	SEVERE_ERROR,
	FATAL_ERROR
};

class LogSender
{
public:
	LogSender(const std::string& senderName);

	const std::string& getSenderName() const;

private:
	std::string m_senderName;

public:
	static const LogSender defaultSender;
};

}

#ifdef ENGINE_ENABLE_LOGGING
	namespace xe
	{
		void internal_engine_log(const LogSender& logSender, const LogLevel& logLevel, const std::string& logMessage);
	}
#   define ENGINE_LOG(logSender, logLevel, logMessage) xe::internal_engine_log(logSender, logLevel, logMessage)
#else
#   define ENGINE_LOG(logSender, logLevel, logMessage)
#endif