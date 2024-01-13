
#include <ParserJsonFiles.hpp>
// #include <ParserYamlFiles.hpp>
#include <iostream>
// #include <stack>
// #include <variant>
// #include <yaml-cpp/yaml.h>

using namespace clg_parserfilescpp;

// const char* cheackTypeNode(const YAML::Node& node)
// {
// 	switch (node.Type())
// 	{
// 		case YAML::NodeType::Null: return "Null";
// 		case YAML::NodeType::Scalar: return "Scalar";
// 		case YAML::NodeType::Sequence: return "Sequence";
// 		case YAML::NodeType::Map: return "Map";
// 		case YAML::NodeType::Undefined: return "Undefined";
// 		default: return "Not";
// 	}
// }
// template<typename T1, typename T2 = T1>
// std::variant<std::string, std::vector<T1>,
// 	int, std::map<std::string, void, T2>> convertTypeNode(const YAML::Node& node)
// {
// 	switch (node.Type())
// 	{
// 		case YAML::NodeType::Null: return;
// 		case YAML::NodeType::Scalar: return node.as<std::string>();
// 		case YAML::NodeType::Sequence: return node.as<std::vector<T1>>();
// 		case YAML::NodeType::Map: return node.as<std::map<std::string, T2>>();
// 		case YAML::NodeType::Undefined: return node.as<int>();
// 		default: return;
// 	}
// }
//
// template<typename T1, typename T2 = nullptr_t>
// struct TY
// {
// 	std::vector<std::variant<int, std::string, double,
// 		std::vector<T1>, TY, T2>> p;
// };
//
// template<typename T = nullptr_t>
// TY<T> te(const YAML::Node& node, const std::string& key)
// {
// 	TY<T> t;
//
// 	for (auto it = node.begin(); it != node.end(); ++it)
// 	{
// 		if (cheackTypeNode(it->second) == "Null"
// 			|| cheackTypeNode(it->second) == "Map")
// 		{
// 			continue;
// 		}
// 		t.p.emplace_back(convertTypeNode<std::string>(it->second));
// 	}
//
// 	return t;
// }
//
// std::stack<YAML::Node> st_node;
// template<typename T>
// T tess(const YAML::Node& node, const std::string& key, bool ui = false)
// {
//
// 	for (auto it = node.begin(); it != node.end(); ++it)
// 	{
// 		if (key == get<std::string>(convertTypeNode<std::string>(it->first))
// 			|| ui)
// 		{
// 			if (cheackTypeNode(it->second) == "Map")
// 			{
// 				st_node.push(it->second);
// 				auto io = tess<YAML::Node>(it->second, key, true);
//
// 			}
// 		}
// 	}
//
// }

int main()
{

	ParserJsonFiles pjf;
	const int ui = pjf.read<int>("Setting_game.json", "l");
	std::cout << ui << std::endl;

	// ParserYamlFiles PYF;
	// const auto ui = PYF.read<TemplateStructYaml>(
	// 	"text.yml", "startMenu");
	//
	// std::cout << ui.title << std::endl;;

	// YAML::Node config = YAML::LoadFile("text.yml");
	//
	// const std::string key = "startMenu"; // <--- key

	// std::map<std::string, std::variant<std::string,
	// 	std::vector<std::string>>> io;
	//
	// TY<TY<std::vector<std::string>>, std::vector<std::string>> t; // struct inventory
	// TY<std::vector<std::string>> t2;

	// const auto [p] = te<TY<TY<std::vector<std::string>>,
	// 					   std::vector<std::string>>>(config, key);
	// std::cout << te[0] << std::endl;

	// for(auto it = config.begin(); it != config.end(); ++it) {
	// 	if (key == it->first.as<std::string>())
	// 	{
	// 		auto op = it->second;
	//
	// 		std::cout << op << std::endl;
	// 		for (auto i = op.begin(); i != op.end(); ++i)
	// 		{
	//
	// 			if (tes(i->second) == "Map")
	// 			{
	// 				for (auto j = i->second.begin(); j != i->second.end(); ++j)
	// 				{
	// 					if (tes(j->second) == "Scalar")
	// 					{
	// 						t2.p.emplace_back(j->second.as<std::string>());
	// 					}
	// 					else
	// 					{
	// 						t2.p.emplace_back(j->second.as<std::vector<std::string>>());
	// 					}
	// 				}
	// 			}
	// 			else
	// 			{
	// 				if (tes(i->second) == "Scalar")
	// 				{
	// 					t.p.emplace_back(i->second.as<std::string>());
	// 				}
	// 				else
	// 				{
	// 					t.p.emplace_back(i->second.as<std::vector<std::string>>());
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	// t.p.emplace_back(t2);

	// std::cout << get<std::vector<std::string>>(p[0])[0];

    return 0;
}
