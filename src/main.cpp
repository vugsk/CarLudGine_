#include <iostream>
#include <utility>
#include <vector>
#include <bits/fs_fwd.h>

#include <CarLudGine/ParserIniFiles.hpp>
#include <CarLudGine/ParserJsonFiles.hpp>

typedef std::string string;

class Error_ final : public std::exception
{
public:
    explicit Error_(string message)
        : message(std::move(message)) {}

    [[nodiscard]] const char* what() const noexcept override
    {
        return message.c_str();
    }

private:
    string message;
};

typedef nlohmann::json json;

static json RetrievesDataFromFile(const char* name)
{
    std::ifstream file(name);
    json          data = json::parse(file);
    file.close();
    return data;
}

template<typename T>
class IParserFile
{
public:
    virtual   ~IParserFile() = default;
    virtual T read_test(const char* key, const char* name) = 0;

};

template<typename T>
class ParserJsonFile final : public IParserFile<T>
{
public:
    ParserJsonFile()
        : m_isMethodBeenRunLeastOnce(false) {}

    T read_test(const char* key, const char* name) override
    {
        return readValueByKeyFromFile(key, RetrievesDataFromFile(name));
    }

protected:
    [[nodiscard]] T readValueByKeyFromFile(const char* key, const json& data)
    {
        if (!m_isMethodBeenRunLeastOnce)
            m_stackData.push(data);

        for (auto& i : data.items())
        {
            if (i.key() == key)
                break;
            if (i.key() != key && !m_stackData.top().empty()
                && !i.value().is_object())
            {
                m_stackData.top().erase(i.key());
            }
            if (i.value().is_object())
            {
                m_stackKey.push(i.key().c_str());
                m_isMethodBeenRunLeastOnce = false;
                return readValueByKeyFromFile(key, i.value());
            }
        }

        if (m_stackData.top().is_object() && m_stackData.top().empty())
        {
            m_stackData.pop();
            m_stackData.top().erase(m_stackKey.top());
            m_stackKey.pop();
            m_isMethodBeenRunLeastOnce = true;
            return readValueByKeyFromFile(key, m_stackData.top());
        }

        return data[key];
    }

private:
    std::stack<const char*> m_stackKey;
    std::stack<json>        m_stackData;
    bool                    m_isMethodBeenRunLeastOnce;
};


// -------------------- PasrserJson ----------------------
class ParserJson
{
public:
    ParserJson()
        : m_isMethodBeenRunLeastOnce(false) {}

    ParserJson(const ParserJson& other)                = delete;
    ParserJson(ParserJson&& other) noexcept            = delete;
    ParserJson& operator=(const ParserJson& other)     = delete;
    ParserJson& operator=(ParserJson&& other) noexcept = delete;
    ~ParserJson()                                      = default;

    template<typename T1>
    [[nodiscard]] T1 readValueByKeyFromFile(const char* key, const json& data)
    {
        if (!m_isMethodBeenRunLeastOnce)
            m_stackData.push(data);

        for (auto& i : data.items())
        {
            if (i.key() == key)
                break;
            if (i.key() != key && !m_stackData.top().empty()
                && !i.value().is_object())
            {
                m_stackData.top().erase(i.key());
            }
            if (i.value().is_object())
            {
                m_stackKey.push(i.key().c_str());
                m_isMethodBeenRunLeastOnce = false;
                return readValueByKeyFromFile<T1>(key, i.value());
            }
        }

        if (m_stackData.top().is_object() && m_stackData.top().empty())
        {
            m_stackData.pop();
            m_stackData.top().erase(m_stackKey.top());
            m_stackKey.pop();
            m_isMethodBeenRunLeastOnce = true;
            return readValueByKeyFromFile<T1>(key, m_stackData.top());
        }

        return data[key];
    }

    template<typename T1>
    void test_write(const char* key, const T1& data)
    {
        add(m_dataWriteInFile, key, data);
    }

    void test_close(const char* name)
    {
        if (!exists(std::filesystem::path{name}) ||
            is_empty(std::filesystem::path{name}))
        {
            writeInFile(name);
        }
        else
        {
            add(RetrievesDataFromFile(name), m_dataWriteInFile);
            writeInFile(name);
        }
        m_dataWriteInFile.clear();
    }

protected:
    template<typename T1>
    static void add(json& data, const char* key, const T1& value)
    {
        data[key] = value;
    }

    static void add(const json& whereFromData, json& whereData)
    {
        for (const auto& i : whereFromData.items())
            add(whereData, i.key().c_str(), i.value());
    }

    void writeInFile(const char* name) const
    {
        std::ofstream file(name);
        file << m_dataWriteInFile.dump(4);
        file.close();
    }

private:
    json                    m_dataWriteInFile;
    std::stack<const char*> m_stackKey;
    std::stack<json>        m_stackData;
    bool                    m_isMethodBeenRunLeastOnce;
};

// -------------------- Pasrser ----------------------
class Parser
{
public:
    Parser()                        = default;
    Parser(const Parser& other)     = default;
    Parser(Parser&& other) noexcept = default;
    ~Parser()                       = default;

    template<typename T>
    [[nodiscard]] T read(const string& name, const string& key)
    {
        formatFile(name);
        existFile(name);
        emptyFile(name);

        if (findFormatFile(name) == m_formatFiles[0])
        {
            ParserJsonFile<T> parser_json_file;
            return parser_json_file.read_test(key.c_str(),
                name.c_str());
        }
        else if (findFormatFile(name) == m_formatFiles[1])
        {
            // class ParserIniFiles method read
            // ...
        }

        doWork("Error: ???");
    }

    // template<typename T>
    // void write(const string& key, const T& data)
    // {
    //     parser_json.test_write(key.c_str(), data);
    // }
    //
    // void close(const string& name)
    // {
    //     if (m_formatFiles[0] == findFormatFile(name))
    //         parser_json.test_close(name.c_str());
    // }

protected:
    //! rename
    static void doWork(const char* err_text)
    {
        try
        {
            throw Error_{err_text};
        }
        catch (const std::exception& err)
        {
            printf("%s", err.what());
        }

        // printf(err_text);
        // exit(EXIT_FAILURE);
    }

    //! rename
    static void formatFile(const string& name)
    {
        for (auto count = 0; const auto& i : m_formatFiles)
        {
            if (!name.ends_with(i) && count++ == m_formatFiles.size() - 1)
                doWork("Error: not format file!!!");
        }
    }

    //! rename
    static void existFile(const string& name)
    {
        if (!exists(std::filesystem::path{name}))
            doWork("Error: not exist file!!!");
    }

    //! rename
    static void emptyFile(const string& name)
    {
        if (is_empty(std::filesystem::path{name}))
            doWork("Error: empty file!!!");
    }

    //! rename
    static string findFormatFile(const string& name)
    {
        return name.substr(name.find_last_of('.') + 1);
    }

    //! rename
    static void addListFormatFiles(const string& format)
    {
        m_formatFiles.push_back(format);
    }

    //! rename
    static void removeListFormatFiles(const string& format)
    {
        if (format == m_formatFiles[0] || format == m_formatFiles[1])
            doWork(("Error: not delete " + format).c_str());
        m_formatFiles.erase(std::ranges::find(m_formatFiles, format));
    }

    //! rename
    static const string& getListFormatFiles(const size_t index)
    {
        return m_formatFiles[index];
    }

    // template<typename T>
    // static void addParser(const T& parser)
    // {
    //     m_parsers<T>.push_back(parser);
    // }
    //
    // template<typename T>
    // static void removeParser(const int index)
    // {
    //     m_parsers<T>.erase(m_parsers<T>.begin() + index);
    // }

private:
    static std::vector<string> m_formatFiles;
    // static ParserJson          parser_json;
};

std::vector<string> Parser::m_formatFiles{"json", "ini"};

// ParserJson Parser::parser_json;




int main()
{
    const string fileIni  = "text.ini";
    const string fileJson = "Setting_game.json";
    const string key      = "TestInterfaceMenu.title";

    Parser p;
    std::cout << p.read<int>(fileJson, "hj") << '\n';
    std::cout << p.read<int>(fileJson, "kl") << '\n';
    std::cout << p.read<int>(fileJson, "l") << '\n';
    std::cout << p.read<int>(fileJson, "did") << '\n';
    std::cout << p.read<int>(fileJson, "gh") << '\n';
    std::cout << p.read<string>(fileJson, "kd") << '\n';

    // p.write("kol", 89);
    // p.write("hj", "gyhd"); //! not write -> fix
    // p.close("test.json");


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
