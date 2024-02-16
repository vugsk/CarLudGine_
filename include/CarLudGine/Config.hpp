
#pragma once

#include <cstring>
#include <functional>
#include <string>
#include <typeindex>

#define DEBUG_MAIN             false
#define DEBUG_CURSES_CPP       false
#define DEBUG_PARSER_FILE_INI  false
#define DEBUG_PARSER_FILE_JSON false
#define DEBUG_SOUNG_CONTROL    false

#if DEBUG_MAIN
  #include <iostream>

  #if DEBUG_CURSES_CPP
    #define WINDOW_CL "Window"
    #define CONTROL_KEYBOARD_CL "ControlKeyboard"
    #define STYLE_WINDOW_CL "StyleWindow"
  #elif DEBUG_PARSER_FILE_JSON
    #define PARSER_JSON_FILES_CL "ParserJsonFiles"
  #elif DEBUG_PARSER_FILE_INI
    #define PARSER_INI_FILES_CL "ParserIniFiles"
  #elif DEBUG_SOUNG_CONTROL
    #define SOUNG_CONTROL_CL "SoungControl"
  #endif

  #define PRINT_CONSTRUCTED_DEBUG(name_class) \
    std::cout << name_class << " constructed" << std::endl;

  #define PRINT_DESTRUCTED_DEBUG(name_class) \
    std::cout << name_class << " destructed" << std::endl;

  #define PRINT_COPY_DEBUG(name_class) \
    std::cout << name_class <<
      " copy constructed" << std::endl;

  #define PRINT_MOVE_DEBUG(name_class) \
    std::cout << name_class <<
      " move constructed" << std::endl;

#endif


template<typename T1, typename T2>
T1 ConvertTypeData(T2 data) { return static_cast<T1>(data); }

template<typename T1, typename T2>
std::pair<T1, T1> ConvertStructPairNum(const std::pair<T2, T2>& data)
{
  return std::make_pair(
    ConvertTypeData<T1>(data.first),
    ConvertTypeData<T1>(data.second)
  );
}

inline const char* AddChar(const char *first_summand, const char *second_summand)
{
  const auto ab = new char[strlen(first_summand) + strlen(second_summand)];
  auto count = 0;

  for (auto i = 0; i < strlen(first_summand); i++)
  {
    ab[count++] = first_summand[i];
  }

  for (auto i = 0; i < strlen(second_summand); i++)
  {
    ab[count++] = second_summand[i];
  }

  return ab;
}


namespace clg_cursescpp
{
  #include <curses.h>

  extern const std::pair<int, int> NULL_XY;
  extern const std::pair<short, short> NULL_XY_int16;
  extern std::pair<int, int> MAX_SCREEN_XY;

  const wchar_t* converterCharInWchar(const char* ch);
}

namespace clg_parserfilescpp
{
  static inline const std::unordered_map<std::type_index,
    const std::string> typeName
  {
  	{std::type_index(typeid(int)), "int"},
  	{std::type_index(typeid(double)), "double"},
  	{std::type_index(typeid(float)), "float"},
  	{std::type_index(typeid(std::string)), "string"},
  	{std::type_index(typeid(std::vector<std::string>)), "vstring"},
  	{std::type_index(typeid(std::vector<int>)), "vint"},
  };

}

namespace clg_SoungControl
{

}


