
#pragma once


namespace clg_cursescpp
{
  class IWindow
  {
  public:
    virtual ~IWindow() = default;
    [[nodiscard]] virtual WINDOW* getWindow() const = 0;
    [[nodiscard]] virtual const std::pair<short, short>& getXY() const = 0;

    virtual void movePrintWin(const std::pair<unsigned, unsigned>& xy,
      const char* text, ...) = 0;
    virtual void printWin(const char* text, ...) = 0;

    IWindow & operator=( const IWindow &other )     = delete;
    IWindow & operator=( IWindow &&other ) noexcept = delete;
  };
}