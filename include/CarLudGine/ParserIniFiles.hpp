
#pragma once

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "Config.hpp"
#include "Errors/CError.hpp"


namespace clg_parserfilescpp
{

	class ParserIniFiles
	{
	public:
		ParserIniFiles();
		~ParserIniFiles();
		ParserIniFiles(const ParserIniFiles &other)				   = delete;
		ParserIniFiles(ParserIniFiles &&other) noexcept			   = delete;
		ParserIniFiles &operator=(const ParserIniFiles &other)	   = delete;
		ParserIniFiles &operator=(ParserIniFiles &&other) noexcept = delete;

		template <typename T>
		T read(const char* name, const char* key)
		{
			read_ini( name, pt );
			return pt.get<T>(key);
		}

		template<typename T, typename T2 = std::string>
		T read_v(const char* name, const char* key)
		{
			const char* rt = AddChar(key, ".len");
			const char* ty = AddChar(key, ".key");

			T dataVector(read<int>(name, rt));
			for (auto i = 0; i < dataVector.size(); i++)
			{
				dataVector[i] = read<T2>(name, ty + std::to_string(i));
			}

			delete[] ty;
			delete[] rt;
			return dataVector;
		}

	private:
		boost::property_tree::ptree pt;
	};

};





