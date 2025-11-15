#include "Core.h"

std::vector<std::filesystem::path> searchFile(std::filesystem::path searchInPath, std::string extension)
{
	std::vector<std::filesystem::path> result;
	try
	{
		for (const auto& entry : std::filesystem::directory_iterator(searchInPath))
		{
			if (extension == "")
			{
				if (entry.is_directory())
				{
					result.emplace_back(entry.path());
				}
			}
			else
			{
				if (entry.is_regular_file() && entry.path().extension() == extension)
				{
					result.emplace_back(entry.path());
				}
			}
		}
	}
	catch (const std::filesystem::filesystem_error&)
	{
		OutputLog("SearchFile -> Error");
		return std::vector<std::filesystem::path>();
	}
	return result;
} 