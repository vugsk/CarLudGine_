
#include <Parser.hpp>
#include <iostream>
#include <stack>

using namespace clg_parserfilescpp;

std::stack<std::string> st_key;
std::stack<nlohmann::json> st_data;

template<typename T>
T test_r(const std::string& key, const nlohmann::json& data = nullptr, const bool test = false) {
    if (!test) st_data.push(data);
    for (auto& [keys, values]: data.items())
    {
        if (keys == key) break;
        if (keys != key && !st_data.top().empty() && !values.is_object())
        {
            st_data.top().erase(keys);
            continue;
        }
        if (values.is_object()) {
            st_key.push(keys);
            return test_r<T>(key, values);
        }
    }
    if (st_data.top().is_object() && st_data.top().empty())
    {
        st_data.pop();
        st_data.top().erase(st_key.top());
        st_key.pop();
        return test_r<T>(key, st_data.top(), true);
    }
    return data[key];
}

int main()
{

    const int ui = read<int>("Setting_game.json", "l",
        [](const char* key, const nlohmann::json& data) {
            return test_r<int>(key, data);
    });

    std::cout << ui << std::endl;

    return 0;
}