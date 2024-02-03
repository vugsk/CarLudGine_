
#pragma once

#include <iostream>
#include <stack>
#include <yaml-cpp/yaml.h>


namespace clg_parserfilescpp
{

	// constexpr bool CheackKeyInFile( const string &key, const YAML::Node &data )
	// {
	// 	for (auto& i : data)
	// 	{
	// 		if (key == i.first.as<string>()) { return true; }
	// 		if (i.second.IsMap()) { return CheackKeyInFile( key, i.second ); }
	// 	}
	// 	return false;
	// }
	// void FuncError(const string &key, const YAML::Node& data)
	// {
	// 	if (!CheackKeyInFile( key, data ))
	// 	{
	// 		cout << "No, key -> " << key << endl;
	// 		exit( EXIT_FAILURE );
	// 	}
	// }

	struct ConfData
	{
		const char* name;
		size_t		size;
	};

	template<typename T1, typename T2>
	struct Data
	{
		T1              name;
		std::vector<T2> vec;
	};

	const char* IsFunc(const YAML::Node& data);

	class ParserYamlFiles
	{
	public:
		ParserYamlFiles()											 = default;
		~ParserYamlFiles()											 = default;
		ParserYamlFiles(const ParserYamlFiles &other)				 = delete;
		ParserYamlFiles(ParserYamlFiles &&other) noexcept			 = delete;
		ParserYamlFiles& operator=(const ParserYamlFiles &other)	 = delete;
		ParserYamlFiles& operator=(ParserYamlFiles &&other) noexcept = delete;

		template<typename T1, typename T2 = T1>
		std::pair<const ConfData, const Data<T1, T2>> read(
			const char* name, const char* key)
		{
			return generateFunc<T1, T2>(
				FindKeyInFile( key, readInFile( name ) )
			);
		}

	protected:
		static YAML::Node readInFile(const char* name);

		std::pair<const std::string, const YAML::Node> FindKeyInFile(
			const std::string &key, const YAML::Node &data, bool test = false);

		template<typename T1, typename T2>
		std::pair<const ConfData, const Data<T1, T2>> generateFunc(
			const std::pair<const std::string, YAML::Node> &data
		)
		{
			const ConfData cf = { data.first.c_str(), data.second.size() };
			Data<T1, T2> st_data_;

			for (auto i : data.second)
			{
				if ( IsFunc( i.second ) == "str" )
				{
					st_data_.name = i.second.as<std::string>();
				}
				else if ( IsFunc( i.second ) == "arr" )
				{
					if ( IsFunc( i.second[0] ) == "str" )
					{
						st_data_.vec = i.second.as<std::vector<std::string>>();
					}
				}
			}

			std::cout << "kdlsf " << cf.name << std::endl;
			return { cf, st_data_ };
		}

	private:
		std::stack<YAML::Node>   st_node;
		std::stack<std::string>  st_key;
	};
}
