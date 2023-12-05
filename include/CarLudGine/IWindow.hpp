
#pragma once

namespace clg_cursescpp {
  #include <curses.h>
  
  class IWindow
  {
    public:
      virtual ~IWindow() {}
      virtual WINDOW* getWindow() const = 0;
  };

}