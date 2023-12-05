


#include "ControlKeyboard.hpp"

#include "IWindow.hpp"
#include <utility>

/*

    class ControlKeyboard

*/

/*

    Public

*/

void clg_cursescpp::ControlKeyboard::scanWin(const char *str, ...)
{
    va_list args;
    va_start(args, str);
    scan(str, args,  _win);
    va_end(args);
}

void clg_cursescpp::ControlKeyboard::moveScanWin(const std::pair<int, int>& xy, 
    const char *str, ...)
{
    va_list args;
    va_start(args, str);
    scan(str, args, _win, xy);
    va_end(args);
}

const char clg_cursescpp::ControlKeyboard::getCh() { return ::wgetch(_win); }

void clg_cursescpp::ControlKeyboard::eventKeyboard(std::function<void()> func, 
    const char button)
{
    if (button == getCh())
    {
        func();
    }
}

void clg_cursescpp::ControlKeyboard::echo(const bool no_off)
{
    if (!no_off)
    {
        ::noecho();
    }

    ::echo();
}

void clg_cursescpp::ControlKeyboard::curs(const int a)
{
    ::curs_set(a);
}

clg_cursescpp::ControlKeyboard::ControlKeyboard(clg_cursescpp::IWindow& window, 
    const bool echo_no_off, const bool curs_a)
{
    _win = window.getWindow();
    echo(true);
    curs(0);
}

clg_cursescpp::ControlKeyboard::ControlKeyboard(WINDOW* window, 
    const bool echo_no_off, const bool curs_a)
{
    _win = window;
    echo(true);
    curs(0);
}

/*

    Protected

*/

inline void clg_cursescpp::ControlKeyboard::scan(const char *str, va_list args, 
    WINDOW *window, const std::pair<int, int>& xy)
{
    wmove(window, xy.second, xy.first);
    vw_scanw(window, str, args);
}