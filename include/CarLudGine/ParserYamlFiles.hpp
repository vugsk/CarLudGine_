
#pragma once

#include <fstream>
// #include <yaml-cpp/yaml.h>

// namespace YAML
// {
// 	template<typename T>
// 	struct convert<T> {
// 		static Node encode(const T& rhs) {
// 			Node node;
//
// 			return node;
// 		}
//
// 		static bool decode(const Node& node, T& rhs) {
// 			if(!node.IsSequence() || node.size() != 3) {
// 				return false;
// 			}
//
//
// 			return true;
// 		}
// 	};
//
// }

namespace clg_parserfilescpp
{

	class ParserYamlFiles
	{
	public:
		ParserYamlFiles() = default;
		~ParserYamlFiles() = default;
		ParserYamlFiles(const ParserYamlFiles &other) = delete;
		ParserYamlFiles(ParserYamlFiles &&other) noexcept = delete;
		ParserYamlFiles& operator=(const ParserYamlFiles &other) = delete;
		ParserYamlFiles& operator=(ParserYamlFiles &&other) noexcept = delete;

		void read(const char* name, const char* key, auto& test)
		{
			// YAML::Node config = YAML::LoadFile(name);
			// return readFromAFile(key, config);
		}

	protected:
		void readInFile(const char* name);

		// auto readFromAFile(const char* key, YAML::Node& node)
		// {

			// for(YAML::const_iterator it = node.begin(); it!= node.end(); ++it)
			// {
			// 	if (it->first.as<std::string>() == key)
			// 	{
			//
			// 		return 0;
			//
			// 	}
			// }

		// }

	private:

	};
}
