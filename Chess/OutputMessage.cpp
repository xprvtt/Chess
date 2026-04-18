
#include "Core.h"

bool outputMessageToLogFile(std::string message)
{		
	std::ofstream out;
	out.open("Log/log.txt", std::ios::app);

	if (out.is_open())
	{
		out << getCurrentTime() << message.c_str() << std::endl;
		out.close();
		return true;
	}
	return false;
} 