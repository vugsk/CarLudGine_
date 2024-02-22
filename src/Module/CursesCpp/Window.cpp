
#include "CarLudGine/Window.hpp"

#include <clocale>

void clg_cursescpp::initScreen(const bool keypad)
{
    ::setlocale(LC_CTYPE, "");
    ::clg_cursescpp::initscr();
    ::clg_cursescpp::keypad(stdscr, keypad);

    MAX_SCREEN_XY = std::make_pair(static_cast<short>(getmaxx(stdscr)),
                                   static_cast<short>(getmaxy(stdscr)));
}


clg_cursescpp::WINDOW* clg_cursescpp::Window::getWindow() const {
    return _win;
}

void clg_cursescpp::Window::print(const char *text, va_list args,
    const std::pair<unsigned, unsigned> &xy) const
{
    ::clg_cursescpp::wmove(_win, static_cast<int>(xy.second),
        static_cast<int>(xy.first));
    ::clg_cursescpp::vw_printw(_win, text, args);
    ::clg_cursescpp::wrefresh(_win);
}

clg_cursescpp::WINDOW* clg_cursescpp::Window::createWindow(
    const std::pair<unsigned, unsigned> &xy,
    const std::pair<unsigned, unsigned> &size)
{
    return ::clg_cursescpp::newwin(static_cast<int>(xy.second),
                                   static_cast<int>(xy.first),
                                   static_cast<int>(size.second),
                                   static_cast<int>(size.first));
}


short clg_cursescpp::Window::getX() const { return _xy.first; }
short clg_cursescpp::Window::getY() const { return _xy.second; }
void clg_cursescpp::Window::close() const { delwin(_win); }
void clg_cursescpp::Window::refresh() const { ::clg_cursescpp::wrefresh(_win); }

const std::pair<short, short>& clg_cursescpp::Window::getXY() const
{
    return _xy;
}

void clg_cursescpp::Window::movePrintWin( const std::pair<unsigned, unsigned> &xy,
    const char *text, ...)
{
    va_list args;
    va_start(args, text);
    print(text, args, xy);
    va_end(args);
}

void clg_cursescpp::Window::printWin(const char* text, ...)
{
    va_list args;   
    va_start(args, text);
    print(text, args);
    va_end(args);
}


clg_cursescpp::Window::Window(const std::pair<unsigned, unsigned>& xy,
        const std::pair<unsigned, unsigned>& size)
    : _win(createWindow(xy, size))
    , _xy(ConvertStructPairNum<short>(xy))
{

    #if DEBUG_CURSES_CPP
        PRINT_CONSTRUCTED_DEBUG(WINDOW_CL);
    #endif

    ::clg_cursescpp::box(_win, 0, 0);

}

clg_cursescpp::Window::~Window()
{
    #if DEBUG_CURSES_CPP
        PRINT_DESTRUCTED_DEBUG(WINDOW_CL);
    #endif

    close();
}

clg_cursescpp::Window::Window(const Window &other)
    : _xy(other._xy)
{
    if (other._win != nullptr)
    {
        _win = new WINDOW(*other._win);
    }

    #if DEBUG_CURSES_CPP
        PRINT_COPY_DEBUG(WINDOW_CL);
    #endif
}

clg_cursescpp::Window::Window(Window&& other) noexcept 
    : _win(other._win)
    , _xy(std::move(other._xy))
{
    #if DEBUG_CURSES_CPP
        PRINT_MOVE_DEBUG(WINDOW_CL);
    #endif
}
