
#include "ControlKeyboardAndMaus"
#include <curses.h>


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
    scan(str, args, getWin());
    va_end(args);
}

void clg_cursescpp::ControlKeyboard::moveScanWin(const PairNum<int> xy, 
    const char *str, ...)
{
    va_list args;
    va_start(args, str);
    scan(str, args, getWin(), xy);
    va_end(args);
}

const char clg_cursescpp::ControlKeyboard::getCh() { return ::wgetch(getWin()); }

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

/*

    Protected

*/

inline void clg_cursescpp::ControlKeyboard::scan(const char *str, va_list args, WINDOW *window, 
    const PairNum<int> xy)
{
    wmove(window, xy._y, xy._x);
    vw_scanw(window, str, args);
}

clg_cursescpp::pWIN clg_cursescpp::ControlKeyboard::getWin() { return stdscr; }