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
	LogSender();
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

#   define DECLARE_LOG_SENDER_EXTERN(senderVariableName) \
           extern ::xe::LogSender internal_logging_ ## senderVariableName

#   define DEFINE_LOG_SENDER(senderVariableName) \
           ::xe::LogSender internal_logging_ ## senderVariableName ## ( #senderVariableName ## )

#   define ENGINE_LOG(senderVariableName, logLevel, logMessage) \
           ::xe::internal_engine_log(internal_logging_ ## senderVariableName, logLevel, logMessage)

#   define ENGINE_LOG_DEFAULT_SENDER(logLevel, logMessage) \
           ::xe::internal_engine_log(Logger::defaultLogger, logLevel, logMessage)

#else
#   define DECLARE_LOG_SENDER_EXTERN(senderVariableName)
#   define DEFINE_LOG_SENDER(senderVariableName)

#   define ENGINE_LOG(logSender, logLevel, logMessage)
#   define ENGINE_LOG_DEFAULT_SENDER(logLevel, logMessage)
#endif