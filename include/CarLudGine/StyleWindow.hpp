
#pragma once

#include "Config.hpp"


namespace clg_cursescpp
{
  class IWindow;


  // extern const char* WALL_Y_PERPENDICULAR;
  // extern const char* WALL_Y_ANGLE_UNDER_90_DOWN;
  // extern const char* WALL_Y_ANGLE_UNDER_90_TOP;
  // extern const char* WALL_X_IN_PARALLEL;
  // extern const char* WALL_X_ANGLE_UNDER_90_LEFT;
  // extern const char* WALL_X_ANGLE_UNDER_90_RIGHT;

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
    RED
  };

  // TODO: attribute

  class StyleWindow
  {
    public:
      StyleWindow(const IWindow& window);
      StyleWindow(WINDOW* window, 
        const std::pair<short, short>& xy);
      ~StyleWindow();

      void drawWall(
        std::vector<const char*>& vec, 
        const bool isHorizontalOrVertical);
      void decorateColor(const Color& color, const char ch);
      void headerWindow(const char* text);
      void clear();
      void clear(const std::pair<short, short>& begin_xy, 
        const std::pair<short, short>& end_xy);

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
      bool                           _isHasColor;
      WINDOW*                        _win;
      const std::pair<short, short>& _xy;

  };

}



