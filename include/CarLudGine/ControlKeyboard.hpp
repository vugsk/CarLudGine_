
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
      ControlKeyboard(const IWindow& window, bool echo_no_off, bool curs_a);
      ControlKeyboard(WINDOW* window, bool echo_no_off, bool curs_a);
      ~ControlKeyboard();

      void scanWin(const char* text, ...) const;
      void moveScanWin(const std::pair<int, int>& xy, const char* text, ...) const;
      void eventKeyboard(const std::function<void()>& func, char button) const;
      
      [[nodiscard]] int getCh() const;
      static void echo(bool no_off);
      static void curs(int a);

    protected:
      static void scan(const char *str, va_list args,
        WINDOW* window, const std::pair<int, int>& xy = NULL_XY);

    private:
      WINDOW* _win;
  };
}
