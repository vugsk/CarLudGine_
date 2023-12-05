
#pragma once

#include "Config.hpp"


namespace clg_cursescpp
{
  class IWindow;

  typedef unsigned char __int8_u;


  struct ColorRgb
  {
    short red;
    short green;
    short blue;
  };

  enum class Color: __int8_u
  {
    WHITE,
    BLACK,
    GREEN,
    BLUE,
    PURPLE,
    YELLOW,
    RED
  };

  // TODO: attribute

  class StyleWindow
  {
    public:
      StyleWindow(const IWindow& window);
      StyleWindow(WINDOW* window);
      ~StyleWindow();

      void drawWall(const std::pair<int, int> xy);
      void decorateColor(const Color& color, const char ch);
      void headerWindow(const char* text);
      void clear();
      void clear(const std::pair<short, short> begin_xy, 
        const std::pair<short, short> end_xy);

    protected:
      const bool getIsHasColor();
      
      void startColor();
      void initPairColor(short pair_number, 
        short foreground, short background);
      void colorPair(int pair_number);
      void initColor(short color_number, const ColorRgb& rgb);
      void attr(const bool on_off, const unsigned attribute);
      void setAttr(const unsigned attribute);

    private:
      bool isHasColor;
      WINDOW* win;

  };

}



