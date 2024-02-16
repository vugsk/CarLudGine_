
#pragma once

#include "Config.hpp"
#include "IWindow.hpp"


namespace clg_cursescpp {
  void initScreen(bool keypad);

  class Window final : public virtual IWindow
  {
    public:
      Window(const Window &);
      Window(Window &&) noexcept;
      Window &operator=(const Window &) = delete;
      Window &operator=(Window &&)      = delete;
      Window(const std::pair<int, int>& xy, const std::pair<int, int>& size);
      ~Window() override;

      void close() const;
      void refresh() const;
      [[nodiscard]] short getX() const;
      [[nodiscard]] short getY() const;
      [[nodiscard]] const std::pair<short, short>& getXY() const final;

      void movePrintWin(const std::pair<int, int>& xy, const char* text, ...) final;
      void printWin(const char* text, ...) final;

    protected:
      void print(const char *text, va_list args,
        const std::pair<int, int>& xy = NULL_XY) const;
      static WINDOW* createWindow(const std::pair<int, int>& xy,
        const std::pair<int, int>& size);
      [[nodiscard]] WINDOW* getWindow() const final;

    private:
      WINDOW*                 _win;
      std::pair<short, short> _xy;
  };
}