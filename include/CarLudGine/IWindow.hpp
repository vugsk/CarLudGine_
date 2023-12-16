
#pragma once


namespace clg_cursescpp
{

  class IWindow
  {
    public:
      virtual ~IWindow() {}
      virtual WINDOW* getWindow() const = 0;
      virtual const std::pair<short, short>& 
        getXY() const = 0;
  };

  class IWindowPrint
  {
    public:
      virtual ~IWindowPrint() {}
      virtual void movePrintWin(const std::pair<int, int>& xy, 
        const char* text, ...) = 0;
  };

}