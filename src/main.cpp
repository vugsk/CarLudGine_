

#include <iostream>
#include <variant>
#include <vector>
#include <bits/fs_fwd.h>
#include <CarLudGine/ParserIniFiles.hpp>
#include <CarLudGine/ParserJsonFiles.hpp>


template<typename T1, typename T2>
class IParser
{
public:
    virtual    ~IParser() = default;
    virtual T1 test_read(const char*key, const T2&data) = 0;
};

template<typename T>
class ParserJson final : public IParser<T, nlohmann::json>
{
public:
    ~ParserJson() override = default;

    T test_read( const char *key, const nlohmann::json &data ) override
    {
        if (!test)
            st_data.push(data);
        if (T value; !getValue1(key, data, value)
                || getValue(key, value))
            return value;
        return data[key];
    }

    static nlohmann::json readInFile(const char* name)
    {
        std::ifstream file(name);
        nlohmann::json data = nlohmann::json::parse(file);
        file.close();
        return data;
    }

protected:
    bool getValue2( const char *key, T &value,
        const nlohmann::detail::iteration_proxy_value<
            nlohmann::detail::iter_impl<const nlohmann::basic_json<>>> &i )
    {
        if (i.value().is_object())
        {
            st_key.push(i.key().c_str());
            test = false;
            value = test_read(key, i.value());
            return false;
        }
        return true;
    }

    //! rename
    bool getValue1( const char *key, const nlohmann::json &data, T &value )
    {
        for (auto&i : data.items())
        {
            if (i.key() == key)
                break;
            if (i.key() != key && !st_data.top().empty() && !i.value().is_object())
                st_data.top().erase(i.key());
            if (const bool valueb = getValue2(key, value, i); !valueb)
                return valueb;
        }
        return true;
    }

    //! rename
    bool getValue(const char *key, T &value)
    {
        if (st_data.top().is_object() && st_data.top().empty())
        {
            st_data.pop();
            st_data.top().erase(st_key.top());
            st_key.pop();
            test = true;
            value = test_read(key, st_data.top());
            return true;
        }
        return false;
    }

private:
    nlohmann::json			   _dataWriteInFile;
    std::stack<const char*>    st_key;
    std::stack<nlohmann::json> st_data;
    bool test = false;
};



class Parser
{
public:
    Parser() = default;
    Parser( const Parser &other )     = delete;
    Parser( Parser &&other ) noexcept = delete;
    ~Parser()                         = default;


    template<typename T>
    T read(const std::string& name, const std::string& key)
    {
        formatFile(name);
        existFile(name);
        emptyFile(name);

        if (findFormatFile(name) == _formatFiles[0])
        {
            // class ParserJsonFiles method read
            // return readFromFile<T>(key, readInFile(name));
            ParserJson<T> pj;
            return pj.test_read(key.c_str(),
                ParserJson<T>::readInFile(name.c_str()));
        }
        else if (findFormatFile(name) == _formatFiles[1])
        {
            // class ParserIniFiles method read
            // ...
        }

        printf("Error: ???");
        exit(EXIT_FAILURE);
    }


    // class ParserJsonFiles methods write() and close().
    //  Возможность использовать с другими форматами файлов,
    //  которые придумает прогроммист.
    // template<typename T>
    // void write(const std::string& key, const T&& data) {}
    // void close(const std::string& name) {}

protected:
    static void formatFile(const std::string& name)
    {
        for (auto count = 0; const auto& i : _formatFiles)
        {
            if (!name.ends_with(i) && count++ == _formatFiles.size() - 1)
            {
                printf("Error: not format file!!!");
                exit(EXIT_FAILURE);
            }
        }
    }

    static void existFile(const std::string& name)
    {
        if (!exists(std::filesystem::path{name}))
        {
            printf("Error: not exist file!!!");
            exit(EXIT_FAILURE);
        }
    }

    static void emptyFile(const std::string& name)
    {
        if (is_empty(std::filesystem::path{name}))
        {
            printf("Error: empty file!!!");
            exit(EXIT_FAILURE);
        }
    }

    static std::string findFormatFile(const std::string& name)
    {
        return name.substr(name.find_last_of('.') + 1);
    }

    static void addListFormatFiles(const std::string& format)
    {
        _formatFiles.push_back(format);
    }

    static void removeListFormatFiles(const std::string& format)
    {
        if (format == _formatFiles[0] || format == _formatFiles[1])
        {
            printf("Error: not delete %s", format.c_str());
            exit(EXIT_FAILURE);
        }
        _formatFiles.erase(std::ranges::find(
            _formatFiles.begin(), _formatFiles.end(), format));
    }

    static const std::string& getListFormatFiles(const size_t index)
    {
        return _formatFiles[index];
    }

    template<typename T1, typename T2>
    static const IParser<T1, T2>& test_create_fabric(const std::string& formatFile)
    {
        if (formatFile == _formatFiles[0])
            return new ParserJson<T1>();
        return nullptr;
    }


private:
    static std::vector<std::string> _formatFiles;

};

std::vector<std::string> Parser::_formatFiles {"json", "ini"};

int main()
{
    const std::string file = "text.ini";
    const std::string fileJson = "Setting_game.json";
    const std::string key  = "TestInterfaceMenu.title";

    Parser p;
    std::cout << p.read<int>(fileJson, "hj") << '\n';
    std::cout << p.read<int>(fileJson, "kl") << '\n';
    std::cout << p.read<int>(fileJson, "l") << '\n';
    std::cout << p.read<int>(fileJson, "did") << '\n';
    std::cout << p.read<int>(fileJson, "gh") << '\n';
    std::cout << p.read<std::string>(fileJson, "kd") << '\n';

    // clg_parserfilescpp::ParserJsonFiles pjf;
    // std::cout << pjf.read<int>(fileJson.c_str(), "hj") << '\n';
    // std::cout << pjf.read<int>(fileJson.c_str(), "kl") << '\n';
    // std::cout << pjf.read<int>(fileJson.c_str(), "l") << '\n';
    // std::cout << pjf.read<int>(fileJson.c_str(), "did") << '\n';
    // std::cout << pjf.read<int>(fileJson.c_str(), "gh") << '\n';
    // std::cout << pjf.read<std::string>(fileJson.c_str(), "kd") << '\n';

    // clg_parserfilescpp::ParserIni pi;
    // pi.read<std::vector<int>>(file, key);


}
