
#pragma once

#include "Config.hpp"
#include "IWindow.hpp"


namespace clg_cursescpp {
  void initScreen(const bool keypad);

  class Window : public virtual IWindow
  {
    public:
      Window(const Window &);
      Window(Window &&) noexcept;
      Window &operator=(const Window &) = delete;
      Window &operator=(Window &&) = delete;
      
      Window(const std::pair<int, int>& xy, const std::pair<int, int>& lw);
      ~Window() override;

      void close();
      short getX();
      short getY();

      void movePrintWin(std::pair<int, int>& xy, 
        const char* text, ...) ;
      void printWin(const char* text, ...);

    protected:
      void print(const char *text, va_list args, 
        const std::pair<int, int>& xy = NULL_XY);
      WINDOW* createWindow(const std::pair<int, int>& xy, 
        const std::pair<int, int>& lw);
      WINDOW* getWindow() const override final;
    
    private:
      WINDOW*                        _win;
      const std::pair<short, short>& _xy;

  };

}