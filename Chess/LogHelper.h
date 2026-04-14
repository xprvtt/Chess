#pragma once

#include "Core.h"

#define DEBUG

#ifdef DEBUG
	#define OUTPUT_LOG(_StringMessage_) outputMessageToLogFile(_StringMessage_) 
	#define OUTPUT_LOG_ERROR(_StringMessage_) outputMessageToLogFile(std::string("ERROR: ") + _StringMessage_) 
	#define OUTPUT_LOG_WARNING(_StringMessage_) outputMessageToLogFile(std::string("WARNING: ") + _StringMessage_) 
	#define DEBUG_CODE(_debug_code_) _d_code_

#elif
	#define OUTPUT_LOG(_StringMessage_)
	#define OUTPUT_LOG_ERROR(_StringMessage_)
	#define OUTPUT_LOG_WARNING(_StringMessage_)
	#define DEBUG_CODE(_debug_code_)
#endif

/// <summary>
/// Функция выводит сообщение в файл Log/log.txt
/// </summary>
/// <param name="message">Сообщение которое необходимо вывести</param>
/// <returns>true если выведен</returns>
bool outputMessageToLogFile(std::string message);