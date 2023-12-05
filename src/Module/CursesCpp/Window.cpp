
#include "Window.hpp"



void clg_cursescpp::initScreen(const bool keypad)
{
    ::initscr();
    ::keypad(stdscr, keypad);

    MAX_SCREEN_XY = std::make_pair(convertTypeData<short>(getmaxx(stdscr)), 
                                   convertTypeData<short>(getmaxy(stdscr)));

}


/*

    Class Window

*/

/*

    Protected

*/

WINDOW* clg_cursescpp::Window::getWindow() const {
    return _win;
}

void clg_cursescpp::Window::print(const char *text, va_list args, 
    const std::pair<int, int>& xy)
{
    ::wmove(_win, xy.second, xy.first);
    ::vw_printw(_win, text, args);
    ::wrefresh(_win);
}

WINDOW* clg_cursescpp::Window::createWindow(
    const std::pair<int, int>& xy,
    const std::pair<int, int>& widthAndLength)
{
    return ::newwin(xy.second, xy.first, widthAndLength.second, widthAndLength.first);
}

/*

    Public

*/

short clg_cursescpp::Window::getX() { return _xy.first; }
short clg_cursescpp::Window::getY() { return _xy.second; }
void clg_cursescpp::Window::close() { delwin(_win); }


void clg_cursescpp::Window::movePrintWin(std::pair<int, int>& xy, const char* text, ...)
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



/*

    Constructer

*/


clg_cursescpp::Window::Window(const std::pair<int, int>& xy, const std::pair<int, int>& lw)
    : _xy(convertStructPairNum<short, short>(xy))
    , _win(createWindow(xy, lw))
{
    ::box(_win, 0, 0);
}


clg_cursescpp::Window::~Window()
{
    close();
}

clg_cursescpp::Window::Window(const Window &other) 
    : _xy(other._xy)
    , _win(!other._win? new WINDOW(*other._win) : nullptr) {}

clg_cursescpp::Window::Window(Window&& other) noexcept 
    : _xy(std::move(other._xy))
    , _win(std::move(other._win)) {}
