
#pragma once

#include "Config.hpp"

namespace clg_cursescpp
{
  class IWindow;

  extern const std::vector<std::pair<const char*, 
    const char*>> WALL_TYPES;
  
  struct ColorRgb
  {
    short red;
    short green;
    short blue;
  };

  enum class Color: unsigned char
  {
    WHITE,
    BLACK,
    GREEN,
    BLUE,
    PURPLE,
    YELLOW,
    RED,
  };

  // TODO: attribute

  class StyleWindow
  {
    public:
      StyleWindow(IWindow* window);
      ~StyleWindow();

      void drawWall(const size_t lenght, 
        const bool isHorizontalOrVertical,
        const std::pair<short, short>& whereWillStartingWall); //* OK
      
      void decorateColor(const Color& color, const char ch);
      void headerWindow(const char* text); //* OK
      void clear(); //* OK
      void clear(const std::pair<short, short>& begin_xy, 
        const std::pair<short, short>& end_xy); //* OK

    protected:
      const bool getIsHasColor();


      void generateWall(
        const bool isHorizontalOrVertical, 
          std::vector<const char*>& vecSimbols,
          const size_t size = 0); //* OK
      
      void startColor();
      void initPairColor(short pair_number, 
        short foreground, short background);
      void colorPair(int pair_number);
      void initColor(short color_number, const ColorRgb& rgb);
      void attr(const bool on_off, const unsigned attribute);
      void setAttr(const unsigned attribute);

    private:
      bool      _isHasColor;
      IWindow*  _mWin;

  };

}



