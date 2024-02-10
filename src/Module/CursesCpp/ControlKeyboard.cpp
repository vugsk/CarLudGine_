
#include "ControlKeyboard.hpp"
#include "IWindow.hpp"


const char clg_cursescpp::DOWN  = ConvertTypeData<char>(KEY_DOWN); // стрелка вниз
const char clg_cursescpp::UP    = ConvertTypeData<char>(KEY_UP); // стрелка вверх
const char clg_cursescpp::LEFT  = ConvertTypeData<char>(KEY_LEFT); // стрелка влево
const char clg_cursescpp::RIGHT = ConvertTypeData<char>(KEY_RIGHT); // стрелка вправо 

const char clg_cursescpp::KEY_W = 119;
const char clg_cursescpp::KEY_A = 97;
const char clg_cursescpp::KEY_S = 115;
const char clg_cursescpp::KEY_D = 100;
const char clg_cursescpp::KEY_I = 105;
const char clg_cursescpp::KEY_R = 114;
const char clg_cursescpp::KEY_E = 101;
const char clg_cursescpp::ESC   = 27;
const char clg_cursescpp::ENTER = 10;


void clg_cursescpp::ControlKeyboard::scanWin(const char *text, ...) const
{
    va_list args;
    va_start(args, text);
    scan(text, args,  _win);
    va_end(args);
}

void clg_cursescpp::ControlKeyboard::moveScanWin(const std::pair<int, int>& xy, 
    const char *text, ...) const
{
    va_list args;
    va_start(args, text);
    scan(text, args, _win, xy);
    va_end(args);
}

int clg_cursescpp::ControlKeyboard::getCh() const { return ::clg_cursescpp::wgetch(_win); }

void clg_cursescpp::ControlKeyboard::eventKeyboard(
    const std::function<void()>& func, const char button) const
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
        ::clg_cursescpp::noecho();
    }
    ::clg_cursescpp::echo();
}

void clg_cursescpp::ControlKeyboard::curs(const int a)
{
    ::clg_cursescpp::curs_set(a);
}

clg_cursescpp::ControlKeyboard::ControlKeyboard(
    const clg_cursescpp::IWindow& window, const bool echo_no_off,
    const bool curs_a)
{
    #if DEBUG_CURSES_CPP
        PRINT_CONSTRUCTED_DEBUG(CONTROL_KEYBOARD_CL);
    #endif

    _win = window.getWindow();
    echo(echo_no_off);
    curs(curs_a);
}

clg_cursescpp::ControlKeyboard::ControlKeyboard(WINDOW* window,
    const bool echo_no_off, const bool curs_a)
        : _win(checkingForWindow(window))
{
    #if DEBUG_CURSES_CPP
        PRINT_CONSTRUCTED_DEBUG(CONTROL_KEYBOARD_CL);
    #endif

    echo(echo_no_off);
    curs(curs_a);
}

clg_cursescpp::ControlKeyboard::~ControlKeyboard()
{
    #if DEBUG_CURSES_CPP
        PRINT_DESTRUCTED_DEBUG(CONTROL_KEYBOARD_CL);
    #endif
}

/*

    Protected

*/

void clg_cursescpp::ControlKeyboard::scan(const char *str,
    va_list args, WINDOW *window, const std::pair<int, int>& xy)
{
    wmove(window, xy.second, xy.first);
    vw_scanw(window, str, args);
}