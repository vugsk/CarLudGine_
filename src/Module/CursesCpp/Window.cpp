
#include "Window"

#include <curses.h>
#include <utility>


template <typename T1, typename T2>
clg_cursescpp::PairNum<T1> clg_cursescpp::convertStructPairNum(clg_cursescpp::PairNum<T2> data)
{
  return {static_cast<T1>(data._x), static_cast<T1>(data._y)};
}

template<typename T1, typename T2>
T1 clg_cursescpp::convertTypeData(T2 data)
{
    return static_cast<T1>(data);
}

/*

    Class Window

*/

const clg_cursescpp::PairNum<short> clg_cursescpp::Window::SCREEN_XY
{ 
    convertTypeData<short>(getmaxx(stdscr)), 
    convertTypeData<short>(getmaxy(stdscr))
};


int clg_cursescpp::Window::getChar() { return wgetch(_win); }
// TODO erorr
void clg_cursescpp::Window::box(const unsigned a, const unsigned b) { ::box(_win, a, b); }
void clg_cursescpp::Window::close() { delwin(_win); }
void clg_cursescpp::Window::refresh() { wrefresh(_win); }

clg_cursescpp::Window* clg_cursescpp::Window::createWindow(
    const PairNum<int> xy,
    const PairNum<int> widthAndLength)
{
    return new Window(convertStructPairNum<short>(xy),
        newwin(xy._x, xy._y, widthAndLength._x, widthAndLength._y));
}

void clg_cursescpp::Window::update() {}


clg_cursescpp::Window::Window() {}

clg_cursescpp::Window::Window(const PairNum<short> xy, WINDOW* window)
    : _win(window)
    , _xy(xy)
{

}

clg_cursescpp::Window::~Window()
{
    close();
}

clg_cursescpp::Window::Window(const Window &other) 
    : _xy(other._xy)
    , _win(!other._win? new WINDOW(*other._win) : nullptr) {}

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
        _win = nullptr;

        _xy = other._xy;

        other._xy._x = 0;
        other._xy._y = 0;
        other._win = nullptr;
    }

    return *this;
}

