
#pragma once

#include "Config.hpp"

namespace clg_cursescpp {
  
  class IWindow;

  extern const char DOWN; // стрелка вниз
  // convertTypeData<char>(KEY_DOWN);   
  extern const char UP; // стрелка вверх
    // convertTypeData<char>(KEY_UP);       
  extern const char LEFT; // стрелка влево
    // convertTypeData<char>(KEY_LEFT);   
  extern const char RIGHT; // стрелка вправо
    // convertTypeData<char>(KEY_RIGHT); 
  // extern const char KEY_W = 119;
  // extern const char KEY_A = 97;
  // extern const char KEY_S = 115;
  // extern const char KEY_D = 100;
  // extern const char KEY_I = 105;
  // extern const char KEY_R = 114;
  // extern const char KEY_E = 101;
  // extern const char ESC   = 27;
  // extern const char ENTER = 10;
  
  class ControlKeyboard
  {
    public:
      ControlKeyboard(IWindow& win, 
        const bool echo_no_off, const bool curs_a);
      ControlKeyboard(WINDOW* win, 
        const bool echo_no_off, const bool curs_a);

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
