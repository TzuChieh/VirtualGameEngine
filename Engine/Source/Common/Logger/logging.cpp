#include "Common/logging.h"
#include "Common/Logger.h"

using namespace xe;

const LogSender LogSender::defaultSender("default sender");

LogSender::LogSender() : 
	m_senderName("default sender name")
{

}

LogSender::LogSender(const std::string& senderName) :
	m_senderName(senderName)
{

}

const std::string& LogSender::getSenderName() const
{
	return m_senderName;
}

#ifdef ENGINE_ENABLE_LOGGING
namespace xe
{
	void internal_engine_log(const LogSender& logSender, const LogLevel& logLevel, const std::string& logMessage)
	{
		Logger::engineLogger.log(logSender, logLevel, logMessage);
	}
}
#endif