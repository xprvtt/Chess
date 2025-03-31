
#include "Core.h"

bool OutputMessage(string message)
{		
		ofstream out;
		out.open("Log/log.txt", ios::app);

		if (out.is_open())
		{
			out << getCurrentTime() << message << endl;
			out.close();
			return true;
		}
		return false;
}