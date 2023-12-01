
#pragma once

#include <curses.h> 

namespace clg_cursescpp {
  typedef WINDOW* pWIN;
  typedef short    __int16;
  typedef unsigned __int32_u;
  
  template<typename T>
  struct PairNum
  {
    PairNum(T a, T b): _x(a), _y(b) {}
    T _x;
    T _y;
  };

  struct TextXY
  {
    const char* _text;
    bool isTopOrDownWindow;
  };

  extern const PairNum<int> NULL_XY;
  extern const PairNum<__int16> NULL_XY_int16;
  extern const TextXY NULL_TEXT_XY;
  extern PairNum<__int16> MAX_SCREEN_XY;

  const wchar_t* converterCharInWchar(const char* ch);
  
  template<typename T1, typename T2>
  T1 convertTypeData(T2 data) { return static_cast<T1>(data); }
  
  template<typename T1, typename T2>
  PairNum<T1> convertStructPairNum(PairNum<T2> data)
  {
    return {
      convertTypeData<T1>(data._x), 
      convertTypeData<T1>(data._y)
    };
  }

  

}
