
#pragma once

#include "Config.hpp"

namespace clg_cursescpp
{
  class IWindow;

  extern const char SQUARE_BRACKET_LEFT;
  extern const char SQUARE_BRACKET_RIGHT;

  extern const std::vector<std::pair<const char*, const char*>> WALL_TYPES;
  
  struct ColorRgb
  {
    short red;
    short green;
    short blue;
  };

  enum Color: short
  {
    BLACK = 0,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
  };

  // TODO: attribute

  class StyleWindow
  {
  public:
    explicit StyleWindow(IWindow* window);
    ~StyleWindow();

    void drawWall(size_t lenght, bool is_horizontal_or_vertical,
      const std::pair<short, short>& where_will_starting_wall) const; //* OK

    static void decorateColor(const Color& color, char ch);
    void headerWindow(const char* text) const; //* OK
    void clear() const; //* OK
    void clear(const std::pair<short, short>& begin_xy,
      const std::pair<short, short>& end_xy) const; //* OK

  protected:
    [[nodiscard]] bool getIsHasColor() const;

    static void generateWall(bool is_horizontal_or_vertical,
      std::vector<const char*>& vec_simbols, size_t size = 0); //* OK

    static void startColor(); //* OK
    static void initPairColor(short pair_number, short foreground, short background);
    static unsigned long colorPair(int pair_number);
    void initColor(short color_number, const ColorRgb& rgb);
    void attr(bool is_on_off, unsigned attribute);
    void setAttr(unsigned attribute);

  private:
    bool      _isHasColor;
    IWindow*  _mWin;

  };

}



