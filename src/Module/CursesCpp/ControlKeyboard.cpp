
#include "CarLudGine/ControlKeyboard.hpp"
#include "CarLudGine/IWindow.hpp"


const char clg_cursescpp::DOWN  = static_cast<char>(KEY_DOWN);  // стрелка вниз
const char clg_cursescpp::UP    = static_cast<char>(KEY_UP);    // стрелка вверх
const char clg_cursescpp::LEFT  = static_cast<char>(KEY_LEFT);  // стрелка влево
const char clg_cursescpp::RIGHT = static_cast<char>(KEY_RIGHT); // стрелка вправо

const char clg_cursescpp::KEY_W = 119;
const char clg_cursescpp::KEY_A = 97;
const char clg_cursescpp::KEY_S = 115;
const char clg_cursescpp::KEY_D = 100;
const char clg_cursescpp::KEY_I = 105;
const char clg_cursescpp::KEY_R = 114;
const char clg_cursescpp::KEY_E = 101;
const char clg_cursescpp::ESC   = 27;
const char clg_cursescpp::ENTER = 10;


void clg_cursescpp::ControlKeyboard::scanWin(const char *format, ...) const
{
    va_list args;
    va_start(args, format);
    scan(format, args,  _win);
    va_end(args);
}

void clg_cursescpp::ControlKeyboard::moveScanWin(const std::pair<unsigned, unsigned>& xy,
    const char *format, ...) const
{
    va_list args;
    va_start(args, format);
    scan(format, args, _win, xy);
    va_end(args);
}

int clg_cursescpp::ControlKeyboard::getCh() const
    { return ::clg_cursescpp::wgetch(_win); }

void clg_cursescpp::ControlKeyboard::eventKeyboard(
    const std::function<void()>& event, const char button_sibols) const
{
    if (button_sibols == getCh())
    {
        event();
    }
}

void clg_cursescpp::ControlKeyboard::echo(const bool is_no_off)
{
    if (!is_no_off)
    {
        ::clg_cursescpp::noecho();
    }
    ::clg_cursescpp::echo();
}

void clg_cursescpp::ControlKeyboard::curs(const unsigned num)
{
    ::clg_cursescpp::curs_set(static_cast<int>(num));
}

clg_cursescpp::ControlKeyboard::ControlKeyboard(
    const IWindow& window, const bool is_echo_no_off,
    const unsigned is_curs)
{
    #if DEBUG_CURSES_CPP
        PRINT_CONSTRUCTED_DEBUG(CONTROL_KEYBOARD_CL);
    #endif

    _win = window.getWindow();
    echo(is_echo_no_off);
    curs(is_curs);
}

clg_cursescpp::ControlKeyboard::ControlKeyboard(WINDOW* window,
    const bool is_echo_no_off, const unsigned is_curs)
        : _win(window ? window : nullptr)
{
    #if DEBUG_CURSES_CPP
        PRINT_CONSTRUCTED_DEBUG(CONTROL_KEYBOARD_CL);
    #endif

    echo(is_echo_no_off);
    curs(is_curs);
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
    va_list args, WINDOW *window, const std::pair<unsigned, unsigned>& xy)
{
    wmove(window, static_cast<int>(xy.second), static_cast<int>(xy.first));
    vw_scanw(window, str, args);
}