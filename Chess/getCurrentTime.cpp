#include "Core.h"

std::string getCurrentTime()
{
    time_t seconds = time(NULL);
    tm timeinfo;

    localtime_s(&timeinfo, &seconds);

    char buffer[50];
    strftime(buffer, sizeof(buffer), " [%Y-%m-%d %H:%M:%S] ", &timeinfo);

    return std::string(buffer);
} 

std::wstring getCurrentTimeWstring()
{
    time_t seconds = time(NULL);
    tm timeinfo;

    localtime_s(&timeinfo, &seconds);

    wchar_t buffer[50];
    wcsftime(buffer, sizeof(buffer), L" [%Y-%m-%d %H:%M:%S] ", &timeinfo);

    return std::wstring(buffer);
}