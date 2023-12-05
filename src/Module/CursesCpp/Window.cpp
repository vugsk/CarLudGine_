
#include "Window.hpp"
#include <utility>

/*

    Initalizate screen and X, Y - screen

*/

void clg_cursescpp::initScreen(const bool keypad)
{
    ::initscr();
    ::keypad(stdscr, keypad);

    MAX_SCREEN_XY = {
        convertTypeData<__int16>(getmaxx(stdscr)), 
        convertTypeData<__int16>(getmaxy(stdscr))
    };

}


/*

    Class Window

*/

/*

    Protected

*/

/*

    get

*/

clg_cursescpp::pWIN clg_cursescpp::Window::getWindow() const {
    return _win;
}


/*

    Print and createWindow

*/

void clg_cursescpp::Window::print(const char *text, va_list args, 
    clg_cursescpp::PairNum<int> xy)
{
    wmove(_win, xy._y, xy._x);
    vw_printw(_win, text, args);
    wrefresh(_win);
}

clg_cursescpp::pWIN clg_cursescpp::Window::createWindow(
    const PairNum<int> xy,
    const PairNum<int> widthAndLength)
{
    return ::newwin(xy._y, xy._x, widthAndLength._y, widthAndLength._x);
}

/*

    Public

*/

/*

    get

*/

clg_cursescpp::__int16 clg_cursescpp::Window::getX() { return _xy._x; }
inline clg_cursescpp::__int16 clg_cursescpp::Window::getY() { return _xy._y; }
void clg_cursescpp::Window::close() { delwin(_win); }


/*

    Print

*/

void clg_cursescpp::Window::movePrintWin(PairNum<int> xy, const char* text, ...)
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


clg_cursescpp::Window::Window(PairNum<int> xy, PairNum<int> lw)
        // const TextXY title 
    : _xy(convertStructPairNum<__int16>(xy))
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
    , _win(!other._win? new WINDOW(*other._win) : nullptr) {
        movePrintWin({5, 5}, "copy");
    }

clg_cursescpp::Window::Window(Window&& other) noexcept 
    : _xy(std::move(other._xy))
    , _win(std::move(other._win)) {}

clg_cursescpp::Window& clg_cursescpp::Window::operator=(const Window &other)
{
    if (this != &other)
    {
        if (!_win)
        {
            _win = new WINDOW(*other._win);
        }
        else 
        {
            _win = nullptr;
        }

        _xy = other._xy;
    }

    return *this;
}

clg_cursescpp::Window& clg_cursescpp::Window::operator=(Window &&other) noexcept
{
    if (this != &other)
    {
        _win = std::move(other._win);
        _xy = std::move(other._xy);
    }

    return *this;
}

