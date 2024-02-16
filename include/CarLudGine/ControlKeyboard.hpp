
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
  protected:
    static void scan(const char *str, va_list args,
      WINDOW* window, const std::pair<unsigned, unsigned>& xy = NULL_XY);

  private:
    WINDOW* _win;

  public:
    ControlKeyboard(const IWindow& window, bool is_echo_no_off, bool is_curs);
    ControlKeyboard(WINDOW* window, bool is_echo_no_off, bool is_curs);
    ~ControlKeyboard();

    void scanWin(const char* format, ...) const;
    void moveScanWin(const std::pair<unsigned, unsigned>& xy,
      const char* format, ...) const;
    void eventKeyboard(const std::function<void()>& event, char button_sibols) const;

    [[nodiscard]] int getCh() const;
    static void echo(bool is_no_off);
    static void curs(int num);

  };
}
