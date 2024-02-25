#include <iostream>
#include <utility>
#include <vector>

#include <CarLudGine/ParserIniFiles.hpp>
#include <CarLudGine/ParserJsonFiles.hpp>

typedef std::string string;
typedef nlohmann::json json;


template<typename T1>
class IParser
{
public:
    virtual    ~IParser() = default;
    virtual T1 read_test(const char* key, const char* name) = 0;
    virtual void write_test(const char* key, const T1& data) = 0;
    virtual void close_test(const char* name) = 0;
    virtual void open_test(const char* name) = 0;
};



template<typename T1>
class ParserJson final : public IParser<T1>
{
public:
    ParserJson() : m_isMethodBeenRunLeastOnce(false) {}

    T1 read_test(const char* key, const char* name) override
    {
        return readValueByKeyFromFile(key, retrievesDataFromFile(name));
    }

    void write_test(const char* key, const T1& data) override
    {
        add(m_dataWriteInFile, key, data);
    }

    //! fix
    void close_test(const char* name) override
    {
        if (!exists(std::filesystem::path{name}) ||
            is_empty(std::filesystem::path{name}))
        {
            writeInFile(name);
        }
        else
        {
            add(retrievesDataFromFile(name), m_dataWriteInFile);
            writeInFile(name);
        }
        m_dataWriteInFile.clear();
    }

    //! fix
    void open_test(const char* name) override
    {

    }

protected:
    [[nodiscard]] static json retrievesDataFromFile(const char* name)
    {
        std::ifstream file(name);
        json          data = json::parse(file);
        file.close();
        return data;
    }

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
                m_stackKey.emplace(i.key().c_str());
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

    template<typename T1>
    static void add(json& data, const char* key,
        const T1& value)
    {
        data[key] = value;
    }

    static void add(const json& whereFromData, json& whereData)
    {
        for (const auto& i : whereFromData.items())
            add(whereData, i.key().c_str(), i.value());
    }

    void writeInFile(const char* name)
    {
        std::ofstream file(name);
        file << m_dataWriteInFile.dump(4);
        file.close();
    }

private:
    std::stack<const char*> m_stackKey;
    std::stack<json>        m_stackData;
    bool                    m_isMethodBeenRunLeastOnce;
    json                    m_dataWriteInFile;
};



// -------------------- Pasrser ----------------------
class Parser
{
public:
    Parser() = default;
    Parser(const Parser& other)     = default;
    Parser(Parser&& other) noexcept = default;
    ~Parser() = default;

    template<typename T>
    [[nodiscard]] T read(const string& name, const string& key)
    {
        formatFile(name);
        existFile(name);
        emptyFile(name);

        for (const auto& i : m_test<T>)
        {
            if (i.first == findFormatFile(name))
                return i.second->read_test(key.c_str(), name.c_str());
            else
                doWork("there is no such type of parser");
        }

        doWork("there is not a single parser");
    }

    template<typename T>
    void write(const string& key, const T& data)
    {

        // parser_json.test_write(key.c_str(), data);
    }

    //! fix
    template<typename T>
    void close(const string& name)
    {
        for (const auto& i : m_test<T>)
        {
            if (i.first == findFormatFile(name))
                i.second->close_test(name.c_str());
            else
                doWork("???");
        }
        // if (m_formatFiles[0] == findFormatFile(name))
        //     parser_json.test_close(name.c_str());
    }

    //! fix
    template<typename T>
    void open(const string& name)
    {
        for (const auto& i : m_test<T>)
        {
            if (i.first == findFormatFile(name))
                i.second->open_test(name.c_str());
            else
                doWork("???");
        }
    }

protected:
    //! rename
    static void doWork(const char* err_text)
    {
        printf("Error: %s", err_text);
        exit(EXIT_FAILURE);
    }

    //! rename
    static void formatFile(const string& name)
    {
        for (auto count = 0; const auto& i : m_formatFiles)
        {
            if (!name.ends_with(i) && count++ == m_formatFiles.size() - 1)
                doWork("there is no such file format");
        }
    }

    //! rename
    static void existFile(const string& name)
    {
        if (!exists(std::filesystem::path{name}))
            doWork("the file does not exist");
    }

    //! rename
    static void emptyFile(const string& name)
    {
        if (is_empty(std::filesystem::path{name}))
            doWork("the file is empty");
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
            doWork(("you cannot delete the " + format + " format").c_str());
        m_formatFiles.erase(std::ranges::find(m_formatFiles, format));
    }

    //! rename
    static const string& getListFormatFiles(const size_t index)
    {
        return m_formatFiles[index];
    }

private:
    static std::vector<string> m_formatFiles;

    template<typename T>
    static std::vector<std::pair<string, std::shared_ptr<IParser<T>>>> m_test;

};

std::vector<string> Parser::m_formatFiles{"json", "ini"};

template<typename T>
std::vector<std::pair<string, std::shared_ptr<IParser<T>>>> Parser::m_test
{
    {"json", std::make_shared<ParserJson<T>>()}
};



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
    std::cout << p.read<string>(fileIni, "kl");



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
    return 0;
}
