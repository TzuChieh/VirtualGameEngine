#include "Logger.h"
#include "Common/logging.h"

#include <iostream>

#if _WIN32 || _WIN64
#   define OPERATING_SYSTEM_WINDOWS
#   include <windows.h>
#endif

using namespace xe;

Logger Logger::engineLogger;

void Logger::log(const LogSender& logSender, const LogLevel& logLevel, const std::string& message) const
{
#   ifdef OPERATING_SYSTEM_WINDOWS
		/*
			0 = Black
			8 = Gray

			1 = Blue
			9 = Light Blue

			2 = Green
			A = Light Green

			3 = Aqua
			B = Light Aqua

			4 = Red
			C = Light Red

			5 = Purple
			D = Light Purple

			6 = Yellow
			E = Light Yellow

			7 = White
			F = Bright White
		*/
		const WORD messageColor = 0x08;
		const WORD warningColor = 0x06;
		const WORD errorColor   = 0x0C;

		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		WORD   index = 0;

		// record console settings before modifying them so we can restore them later
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hstdout, &csbi);

		switch(logLevel)
		{
		case LogLevel::NOTE_MESSAGE:
			// set console text color
			SetConsoleTextAttribute(hstdout, messageColor);
			std::cout << "[" << logSender.getSenderName() << "] >> " << message << std::endl;
			break;

		case LogLevel::NOTE_WARNING:
			// set console text color
			SetConsoleTextAttribute(hstdout, warningColor);
			std::cerr << "[" << logSender.getSenderName() << "] warning >> " << message << std::endl;
			break;

		case LogLevel::RECOVERABLE_ERROR:
		case LogLevel::SEVERE_ERROR:
		case LogLevel::FATAL_ERROR:
			// set console text color
			SetConsoleTextAttribute(hstdout, errorColor);
			std::cerr << "[" << logSender.getSenderName() << "] error >> " << message << std::endl;
			break;

		default:
			// set console text color
			SetConsoleTextAttribute(hstdout, warningColor);
			std::cerr << "Logger Warning: use of unsupported log level" << std::endl;
			std::cerr << "message: " << message << std::endl;
			std::cerr << "from: " << logSender.getSenderName() << std::endl;
			break;
		}

		// restore console settings
		SetConsoleTextAttribute(hstdout, csbi.wAttributes);
#   else
		switch(logLevel)
		{
		case LogLevel::MESSAGE:
			std::cout << "[" << logSender.getSenderName() << "] >> " << message << std::endl;
			break;

		case LogLevel::WARNING:
			std::cerr << "[" << logSender.getSenderName() << "] warning >> " << message << std::endl;
			break;

		case LogLevel::ERROR:
			std::cerr << "[" << logSender.getSenderName() << "] error >> " << message << std::endl;
			break;

		default:
			std::cerr << "Logger Warning: use of unsupported log level" << std::endl;
			std::cerr << "message: " << message << std::endl;
			std::cerr << "from: " << logSender.getSenderName() << std::endl;
			break;
		}
#   endif
}
