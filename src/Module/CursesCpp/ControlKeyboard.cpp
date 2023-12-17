


#include "ControlKeyboard.hpp"

#include "IWindow.hpp"


const char clg_cursescpp::DOWN  = convertTypeData<char>(KEY_DOWN);; // стрелка вниз   
const char clg_cursescpp::UP    = convertTypeData<char>(KEY_UP);; // стрелка вверх       
const char clg_cursescpp::LEFT  = convertTypeData<char>(KEY_LEFT);; // стрелка влево   
const char clg_cursescpp::RIGHT = convertTypeData<char>(KEY_RIGHT); // стрелка вправо 

const char clg_cursescpp::KEY_W = 119;
const char clg_cursescpp::KEY_A = 97;
const char clg_cursescpp::KEY_S = 115;
const char clg_cursescpp::KEY_D = 100;
const char clg_cursescpp::KEY_I = 105;
const char clg_cursescpp::KEY_R = 114;
const char clg_cursescpp::KEY_E = 101;
const char clg_cursescpp::ESC   = 27;
const char clg_cursescpp::ENTER = 10;


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
    #if DEBUG
        PRINT_CONSTRUCTED_DEBUG(CONTROL_KEYBOARD_CL);
    #endif

    _win = window.getWindow();
    echo(true);
    curs(0);
}

clg_cursescpp::ControlKeyboard::ControlKeyboard(WINDOW* window, 
    const bool echo_no_off, const bool curs_a)
        : _win(checkingForWindow(window))
{
    #if DEBUG
        PRINT_CONSTRUCTED_DEBUG(CONTROL_KEYBOARD_CL);
    #endif

    echo(true);
    curs(0);
}

clg_cursescpp::ControlKeyboard::~ControlKeyboard()
{
    #if DEBUG
        PRINT_DESTRUCTED_DEBUG(CONTROL_KEYBOARD_CL);
    #endif
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