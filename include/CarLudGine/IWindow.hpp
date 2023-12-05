
#pragma once


namespace clg_cursescpp
{

  class IWindow
  {
    public:
      virtual ~IWindow() {}
      virtual WINDOW* getWindow() const = 0;
  };

}