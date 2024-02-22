

#include <iostream>
#include <vector>
#include <bits/fs_fwd.h>
#include <CarLudGine/ParserIniFiles.hpp>
#include <CarLudGine/ParserJsonFiles.hpp>



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


private:
    static std::vector<std::string> _formatFiles;

};

std::vector<std::string> Parser::_formatFiles {"json", "ini"};

int main()
{
    const std::string file = "text.ini";
    const std::string fileJson = "Setting_game.json";
    const std::string key  = "TestInterfaceMenu.title";

    // Parser p;
    // std::cout << p.read<std::string>(file, key);

    clg_parserfilescpp::ParserJsonFiles pjf;
    std::cout << pjf.read<int>(fileJson.c_str(), "hj") << '\n';
    std::cout << pjf.read<int>(fileJson.c_str(), "kl") << '\n';
    std::cout << pjf.read<int>(fileJson.c_str(), "l") << '\n';
    std::cout << pjf.read<int>(fileJson.c_str(), "did") << '\n';
    std::cout << pjf.read<int>(fileJson.c_str(), "gh") << '\n';

    // clg_parserfilescpp::ParserIni pi;
    // pi.read<std::vector<int>>(file, key);


}
