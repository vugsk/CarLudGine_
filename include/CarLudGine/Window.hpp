
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
      Window &operator=(const Window &);
      Window &operator=(Window &&) noexcept;
      Window(PairNum<int> xy, PairNum<int> lw);
      ~Window() override;

      void close();
      __int16 getX();
      __int16 getY();

      void movePrintWin(PairNum<int> xy, 
        const char* text, ...) ;
      void printWin(const char* text, ...);

    protected:
      void print(const char *text, va_list args, 
        const PairNum<int> xy = NULL_XY);
      pWIN createWindow(const PairNum<int> xy, 
        const PairNum<int> lw);
      pWIN getWindow() const override final;
    
    private:
      pWIN             _win;
      PairNum<__int16> _xy;

  };

}