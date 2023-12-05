
#pragma once

#include <utility>
#include <functional>
#include <curses.h>


namespace clg_cursescpp
{

  struct TextXY
  {
    const char* _text;
    bool isTopOrDownWindow;
  };

  extern const std::pair<int, int> NULL_XY;
  extern const std::pair<short, short> NULL_XY_int16;
  extern const TextXY NULL_TEXT_XY;
  extern std::pair<int, int> MAX_SCREEN_XY;

  const wchar_t* converterCharInWchar(const char* ch);
  
  template<typename T1, typename T2>
  T1 convertTypeData(T2 data) { return static_cast<T1>(data); }
  
  template<typename T1, typename T2, typename T3, typename T4>
  const std::pair<T1, T2>& convertStructPairNum(
    const std::pair<T3, T4>& data)
  {
    return std::make_pair(
      convertTypeData<T3>(data.first), 
      convertTypeData<T4>(data.second)
    );
  }

  

}
