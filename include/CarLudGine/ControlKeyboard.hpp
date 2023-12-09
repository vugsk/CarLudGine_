
#pragma once

#include "Config.hpp"

namespace clg_cursescpp {
  
  class IWindow;

  extern const char DOWN;  // стрелка вниз
  extern const char UP;    // стрелка вверх    
  extern const char LEFT;  // стрелка влево  
  extern const char RIGHT; // стрелка вправо

  extern const char KEY_W;
  extern const char KEY_A;
  extern const char KEY_S;
  extern const char KEY_D;
  extern const char KEY_I;
  extern const char KEY_R;
  extern const char KEY_E;
  extern const char ESC;
  extern const char ENTER;
  
  class ControlKeyboard
  {
    public:
      ControlKeyboard(IWindow& win, 
        const bool echo_no_off, const bool curs_a);
      ControlKeyboard(WINDOW* win, 
        const bool echo_no_off, const bool curs_a);
      ~ControlKeyboard();

      void scanWin(const char* text, ...);
      void moveScanWin(const std::pair<int, int>& xy, 
        const char* text, ...);

      void eventKeyboard(std::function<void()> func, 
        const char button);
      
      const char getCh();

      void echo(const bool no_off);
      void curs(const int a);

    protected:
      inline void scan(const char *str, va_list args, 
        WINDOW* window, const std::pair<int, int>& xy = NULL_XY);

    private:
      WINDOW* _win;
    
  };

}
