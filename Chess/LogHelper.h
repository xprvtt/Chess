#pragma once

#include "Core.h"

#define DEBUG

#ifdef DEBUG
	#define OUTPUT_LOG(__STRING_MESSAGE__) outputMessageToLogFile(__STRING_MESSAGE__) 
	#define OUTPUT_LOG_ERROR(__STRING_MESSAGE__) outputMessageToLogFile(std::string("ERROR: ") + __STRING_MESSAGE__) 
	#define OUTPUT_LOG_WARNING(__STRING_MESSAGE__) outputMessageToLogFile(std::string("WARNING: ") + __STRING_MESSAGE__) 

	#define DEBUG_CODE(__DEBUG_CODE__) __DEBUG_CODE__

#elif
	#define OUTPUT_LOG(__STRING_MESSAGE__)
	#define OUTPUT_LOG_ERROR(__STRING_MESSAGE__)
	#define OUTPUT_LOG_WARNING(__STRING_MESSAGE__)

	#define DEBUG_CODE(__DEBUG_CODE__)
#endif

/// <summary>
/// Функция выводит сообщение в файл Log/log.txt
/// </summary>
/// <param name="message">Сообщение которое необходимо вывести</param>
/// <returns>true если выведен</returns>
bool outputMessageToLogFile(std::string message);