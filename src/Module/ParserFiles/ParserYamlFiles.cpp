
#include "ParserYamlFiles.hpp"


const char* clg_parserfilescpp::IsFunc(const YAML::Node& data)
{
    if (data.IsScalar())
    {
        return "str";
    }
    else if (data.IsNull())
    {
        return "null";
    }
    else if (data.IsDefined())
    {
        return "arr";
    }
    else if (data.IsSequence())
    {
        return "arr2";
    }
    else if (data.IsMap())
    {
        return "map";
    }

    return "Errror";
}


YAML::Node clg_parserfilescpp::ParserYamlFiles::readInFile(const char *name)
{
    return YAML::LoadFile( name );
}


std::pair<const std::string,
          const YAML::Node> clg_parserfilescpp::ParserYamlFiles::FindKeyInFile(
              const std::string &key,
              const YAML::Node  &data,
              const bool         test )
{
    if (!test) { st_node.push(data); }
    for (auto i : data)
    {
        if (key == i.first.as<std::string>()) { break; }
        if (key != i.first.as<std::string>() &&
            !st_node.top().IsNull()		&&
            !i.second.IsMap())
        {
            st_node.top().remove( i.first );
            continue;
        }

        if (i.second.IsMap())
        {
            st_key.push( i.first.as<std::string>() );
            return FindKeyInFile( key, i.second );
        }
    }
    if (st_node.top().IsMap() && st_node.top().IsNull())
    {
        st_node.pop();
        st_node.top().remove( st_key.top() );
        st_key.pop();
        return FindKeyInFile( key, st_node.top(), true );
    }
    return {key, data[key]};
}