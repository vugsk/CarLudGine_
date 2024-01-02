
#pragma once
#include <fstream>
#include <functional>
#include <nlohmann/json.hpp>

namespace clg_parserfilescpp
{
  extern const char* FORMAT_JSON;

  static nlohmann::json dataR;

  template<typename T>
  T read(const char* name, const char* key,
    std::function<T(const char*, const nlohmann::json&)> function)
  {
    std::ifstream file(name);
    dataR = nlohmann::json::parse(file);
    file.close();
    return function(key, dataR);
  }

  // template<typename T>
  // class ReadFile
  // {
  //   public:
  //     virtual ~ReadFile() = default;
  //     virtual T read(const std::string& name, const char* key) = 0;
  // };

  // template<typename T>
  // class WriteFile
  // {
  //   public:
  //     virtual ~WriteFile() = default;
  //     virtual void write(const char* key, T&& data) = 0;
  //     static void close(const char* name)
  //     {
  //       std::ofstream file(name);
  //       file << _dataWrite.dump(4);
  //       file.close();
  //     }
  // };
}
