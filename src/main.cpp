

#include <iostream>
#include <vector>
#include <bits/fs_fwd.h>

#include <CarLudGine/ParserIniFiles.hpp>
#include <CarLudGine/ParserJsonFiles.hpp>


template<typename T1, typename T2> class IParser
{
public:
    virtual ~IParser()                               = default;
    IParser()                                        = default;
    IParser( const IParser &other )                  = delete;
    IParser( IParser &&other ) noexcept              = delete;
    IParser &  operator=( const IParser &other )     = delete;
    IParser &  operator=( IParser &&other ) noexcept = delete;

    virtual T1 readValueByKey_DataFile(const char*key, const T2&data) = 0;
};

typedef nlohmann::json json;


static json RetrievesDataFromFile_json(const char* name)
{
    std::ifstream file(name);
    json data = json::parse(file);
    file.close();
    return data;
}

template<typename T> class ParserJson final : public IParser<T, json>
{
public:
    ParserJson() : m_isMethodBeenRunLeastOnce(false) {}
    ParserJson( const ParserJson &other )                 = delete;
    ParserJson( ParserJson &&other ) noexcept             = delete;
    ParserJson & operator=( const ParserJson &other )     = delete;
    ParserJson & operator=( ParserJson &&other ) noexcept = delete;
    ~ParserJson() override                                = default;

    T readValueByKey_DataFile(const char *key, const json &data) override
    {
        if (!m_isMethodBeenRunLeastOnce)
            m_stackData.push(data);
        if (T value; !isSuchKeyExist(key, data, value)
                || isThereObjectTheStackAndIsEmpty(key, value))
            return value;
        return data[key];
    }

protected:
    // auto -> nlohmann::detail::iteration_proxy_value<
    //      nlohmann::detail::iter_impl< const nlohmann::basic_json<>>>
    [[nodiscard]] constexpr bool isDataAnObject(const char *key,
        const auto &data, T &retun_value)
    {
        if (data.value().is_object())
        {
            m_stackKey.push(data.key().c_str());
            m_isMethodBeenRunLeastOnce = false;
            retun_value = readValueByKey_DataFile(key, data.value());
            return false;
        }
        return true;
    }

    [[nodiscard]] constexpr bool isSuchKeyExist(const char *key,
                                                const json &data, T &return_value)
    {
        for (auto&i : data.items())
        {
            if (i.key() == key)
                break;
            if (i.key() != key && !m_stackData.top().empty()
                               && !i.value().is_object())
                m_stackData.top().erase(i.key());
            if (const bool isDataObject =
                    isDataAnObject(key, i, return_value); !isDataObject)
                return isDataObject;
        }
        return true;
    }

    [[nodiscard]] constexpr bool isThereObjectTheStackAndIsEmpty(const char *key,
                                                                 T &return_value)
    {
        if (m_stackData.top().is_object() && m_stackData.top().empty())
        {
            m_stackData.pop();
            m_stackData.top().erase(m_stackKey.top());
            m_stackKey.pop();
            m_isMethodBeenRunLeastOnce = true;
            return_value = readValueByKey_DataFile(key, m_stackData.top());
            return true;
        }
        return false;
    }

private:
    json m_dataWriteInFile;
    std::stack<const char*> m_stackKey;
    std::stack<json> m_stackData;
    bool m_isMethodBeenRunLeastOnce;

};

class Parser
{
public:
    Parser() = default;
    Parser( const Parser &other )     = delete;
    Parser( Parser &&other ) noexcept = delete;
    ~Parser()                         = default;

    template<typename T>
    [[nodiscard]] T read(const std::string& name, const std::string& key)
    {
        formatFile(name);
        existFile(name);
        emptyFile(name);

        if (findFormatFile(name) == m_formatFiles[0])
        {
            ParserJson<T> parser_json;
            return parser_json.readValueByKey_DataFile(key.c_str(),
                RetrievesDataFromFile_json(name.c_str()));
        }
        else if (findFormatFile(name) == m_formatFiles[1])
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
        for (auto count = 0; const auto& i : m_formatFiles)
        {
            if (!name.ends_with(i) && count++ == m_formatFiles.size() - 1)
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
        m_formatFiles.push_back(format);
    }

    static void removeListFormatFiles(const std::string& format)
    {
        if (format == m_formatFiles[0] || format == m_formatFiles[1])
        {
            printf("Error: not delete %s", format.c_str());
            exit(EXIT_FAILURE);
        }
        m_formatFiles.erase(std::ranges::find(
            m_formatFiles.begin(), m_formatFiles.end(), format));
    }

    static const std::string& getListFormatFiles(const size_t index)
    {
        return m_formatFiles[index];
    }

private:
    static std::vector<std::string> m_formatFiles;

};

std::vector<std::string> Parser::m_formatFiles {"json", "ini"};




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
