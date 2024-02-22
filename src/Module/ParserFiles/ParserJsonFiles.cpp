
#include "CarLudGine/ParserJsonFiles.hpp"
#include "CarLudGine/Config.hpp"

#include <fstream>
#include <bits/fs_ops.h>
#include <bits/fs_path.h>


clg_parserfilescpp::ParserJsonFiles::ParserJsonFiles()
{
	#if DEBUG_PARSER_FILE_JSON
		PRINT_CONSTRUCTED_DEBUG(PARSER_JSON_FILES_CL);
	#endif
}

clg_parserfilescpp::ParserJsonFiles::~ParserJsonFiles()
{
	#if DEBUG_PARSER_FILE_JSON
		PRINT_DESTRUCTED_DEBUG(PARSER_JSON_FILES_CL)
	#endif
}

void clg_parserfilescpp::ParserJsonFiles::close(const char* name)
{
	if (!exists(std::filesystem::path{name})
		|| is_empty(std::filesystem::path{name}))
	{
		writeInFile(name);
	}
	else
	{
		add(readInFile(name), _dataWriteInFile);
		writeInFile(name);
	}
	_dataWriteInFile.clear();
}

nlohmann::json clg_parserfilescpp::ParserJsonFiles::getDataWriteInFile() const
{
	return _dataWriteInFile;
}

nlohmann::json clg_parserfilescpp::ParserJsonFiles::readInFile(const char* name)
{
	std::ifstream file(name);
	nlohmann::json data = nlohmann::json::parse(file);
	file.close();
	return data;
}

void clg_parserfilescpp::ParserJsonFiles::writeInFile(const char* name) const
{
	std::ofstream file(name);
	file << _dataWriteInFile.dump(4);
	file.close();
}

void clg_parserfilescpp::ParserJsonFiles::add(const nlohmann::json &whereFromData,
	nlohmann::json &whereData)
{
	for (auto [keys, values]
		: whereFromData.items())
	{
		add(whereData, keys.c_str(), values);
	}
}
