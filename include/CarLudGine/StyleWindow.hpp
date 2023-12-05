
#pragma once

#include "Config.hpp"


namespace clg_cursescpp
{

  class IWindow;

  typedef unsigned char __int8_u;

  struct ColorRgb
  {
    __int16 red;
    __int16 green;
    __int16 blue;
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
      StyleWindow(const pWIN window);
      ~StyleWindow();

      void drawWall(const PairNum<int> xy);
      void decorateColor(const Color& color, const char ch);
      void headerWindow(const char* text);
      void clear();
      void clear(const PairNum<__int16> begin_xy, 
        const PairNum<__int16> end_xy);

    protected:
      const bool getIsHasColor();
      
      void startColor();
      void initPairColor(__int16 pair_number, 
        __int16 foreground, __int16 background);
      void colorPair(int pair_number);
      void initColor(__int16 color_number, const ColorRgb& rgb);
      void attr(const bool on_off, const unsigned attribute);
      void setAttr(const unsigned attribute);

    private:
      bool isHasColor;
      pWIN win;

  };

}



