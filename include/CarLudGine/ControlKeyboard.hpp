
#pragma once

#include <functional>

#include "Config.hpp"


namespace clg_cursescpp {

  class IWindow;

  static const char DOWN = 
    convertTypeData<char>(KEY_DOWN);   // стрелка вниз
  static const char UP    = 
    convertTypeData<char>(KEY_UP);       // стрелка вверх
  static const char LEFT  = 
    convertTypeData<char>(KEY_LEFT);   // стрелка влево
  static const char RIGHT = 
    convertTypeData<char>(KEY_RIGHT); // стрелка вправо
  static const char KEY_W = 119;
  static const char KEY_A = 97;
  static const char KEY_S = 115;
  static const char KEY_D = 100;
  static const char KEY_I = 105;
  static const char KEY_R = 114;
  static const char KEY_E = 101;
  static const char ESC   = 27;
  static const char ENTER = 10;
  
  class ControlKeyboard
  {
    public:
      ControlKeyboard(IWindow& win, 
        const bool echo_no_off, const bool curs_a);
      ControlKeyboard(pWIN win, 
        const bool echo_no_off, const bool curs_a);

      void scanWin(const char* text, ...);
      void moveScanWin(const PairNum<int> xy, const char* text, ...);

      void eventKeyboard(std::function<void()> func, 
        const char button);
      
      const char getCh();

      void echo(const bool no_off);
      void curs(const int a);

    protected:
      inline void scan(const char *str, va_list args, 
        pWIN window, const PairNum<int> xy = NULL_XY);

    private:
      pWIN _win;
    
  };

}
