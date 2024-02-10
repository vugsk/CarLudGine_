

#include "ParserIniFiles.hpp"


clg_parserfilescpp::ParserIniFiles::ParserIniFiles()
{
	#if DEBUG_PARSER_FILE_INI
		PRINT_CONSTRUCTED_DEBUG(PARSER_INI_FILES_CL);
	#endif
}

clg_parserfilescpp::ParserIniFiles::~ParserIniFiles()
{
	#if DEBUG_PARSER_FILE_INI
		PRINT_DESTRUCTED_DEBUG(PARSER_INI_FILES_CL)
	#endif
}
