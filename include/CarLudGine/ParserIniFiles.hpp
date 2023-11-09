
#pragma once

#include <string>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace clg_parserfilescpp
{
	// static inline std::unordered_map<std::type_index, std::string> type_name
	// {
	// 	{std::type_index(typeid(int)), "int"},
	// 	{std::type_index(typeid(double)), "double"},
	// 	{std::type_index(typeid(float)), "float"},
	// 	{std::type_index(typeid(std::string)), "string"},
	// 	{std::type_index(typeid(std::vector<std::string>)), "vstring"},
	// 	{std::type_index(typeid(std::vector<int>)), "vint"},
	// };

	class ParserIniFiles
	{
	public:
		ParserIniFiles() = default;
		~ParserIniFiles() = default;
		explicit ParserIniFiles(const boost::property_tree::ptree &pt) : pt(pt) {}
		ParserIniFiles(const ParserIniFiles &other) = delete;
		ParserIniFiles(ParserIniFiles &&other) noexcept = delete;
		ParserIniFiles &operator=(const ParserIniFiles &other) = delete;
		ParserIniFiles &operator=(ParserIniFiles &&other) noexcept = delete;

		template <typename T>
		T read(const std::string& name, const std::string& key)
		{
			boost::property_tree::ini_parser::read_ini( name, pt );
			return pt.get<T>(key);
		}

		template<typename T, typename T2 = std::string>
		T read_v(const std::string& name, const std::string& key)
		{
			T dataVector(read<int>(name, key + ".len"));

			for (auto i = 0; i < dataVector.size(); i++)
			{
				dataVector[i] = read_v<T2>(
					name, key + ".key" + std::to_string(i));
			}

			return dataVector;
		}

	protected:

	private:
		boost::property_tree::ptree pt;

	};

}


