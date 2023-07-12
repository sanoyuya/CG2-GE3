#include "File.h"

std::vector<std::string> GetFileNames(const std::string& folderPath)
{
	std::filesystem::directory_iterator iter(folderPath), end;
	std::error_code err;
	std::vector<std::string> file_names;

	for (; iter != end && !err; iter.increment(err))
	{
		const std::filesystem::directory_entry entry = *iter;

		file_names.push_back(entry.path().string());
	}

	return file_names;
}