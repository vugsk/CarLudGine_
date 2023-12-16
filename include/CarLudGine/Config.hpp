
#pragma once

#include <utility>
#include <functional>
#include <vector>
#include <curses.h>



#define DEBUG false

#if DEBUG
  #include <iostream>

  #define WINDOW_CL "Window"
  #define CONTROL_KEYBOARD_CL "ControlKeyboard"
  #define STYLE_WINDOW_CL "StyleWindow"

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


namespace clg_cursescpp
{
 
  extern const std::pair<int, int> NULL_XY;
  extern const std::pair<short, short> NULL_XY_int16;
  extern std::pair<int, int> MAX_SCREEN_XY;

  const wchar_t* converterCharInWchar(const char* ch);
  
  template<typename T1, typename T2>
  T1 convertTypeData(T2 data) { return static_cast<T1>(data); }
  
  template<typename T1, typename T2>
  const std::pair<T1, T1> convertStructPairNum(
    const std::pair<T2, T2>& data)
  {
    return std::make_pair(
      convertTypeData<T1>(data.first), 
      convertTypeData<T1>(data.second)
    );
  }

  WINDOW* checkingForWindow(WINDOW* window);

}
