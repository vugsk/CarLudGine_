
#include "Window"

#include <cstdlib>
#include <cstring>
#include <cwchar>



const clg_cursescpp::PairNum<int> clg_cursescpp::NULL_XY = {
    0, 0
};

const clg_cursescpp::TextXY clg_cursescpp::NULL_TEXT_XY = {
    "", 0
};

clg_cursescpp::PairNum<clg_cursescpp::__int16> clg_cursescpp::MAX_SCREEN_XY = {
    0, 0
};

template <typename T1, typename T2>
clg_cursescpp::PairNum<T1> clg_cursescpp::convertStructPairNum(PairNum<T2> data)
{
  return {static_cast<T1>(data._x), static_cast<T1>(data._y)};
}

template<typename T1, typename T2>
T1 clg_cursescpp::convertTypeData(T2 data)
{
    return static_cast<T1>(data);
}

const wchar_t* clg_cursescpp::converterCharInWchar(const char* ch)
{
    size_t cSize = strlen(ch)+1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs (wc, ch, cSize);
    return wc;
}

void clg_cursescpp::initScreen()
{
    ::initscr();

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

inline const char* clg_cursescpp::Window::getTitle() {
    return _title;
}

inline clg_cursescpp::pWIN clg_cursescpp::Window::getWindow() {
    return _win;
}

inline void clg_cursescpp::Window::print(const char *text, va_list args, 
    clg_cursescpp::PairNum<int> xy)
{
    wmove(_win, xy._y, xy._x);
    vw_printw(_win, text, args);
    wrefresh(_win);
}

inline clg_cursescpp::pWIN clg_cursescpp::Window::createWindow(
    const PairNum<int> xy,
    const PairNum<int> widthAndLength)
{
    return ::newwin(xy._y, xy._x, widthAndLength._y, widthAndLength._x);
}

/*

    Public

*/

inline clg_cursescpp::__int16 clg_cursescpp::Window::getX() { return _xy._x; }
inline clg_cursescpp::__int16 clg_cursescpp::Window::getY() { return _xy._y; }
inline void clg_cursescpp::Window::close() { delwin(_win); }


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


clg_cursescpp::Window::Window(PairNum<int> xy, PairNum<int> lw, const TextXY title) 
    : _xy(convertStructPairNum<__int16>(xy))
    , _win(createWindow(xy, lw))
{
    ::box(_win, 0, 0);

    if (!strlen(title._text)) {
        __int16 x = convertTypeData<__int16>((_xy._x / 2) - 
            (std::wcslen(converterCharInWchar(title._text)) / 2));
        
        if (title.isTopOrDownWindow)
        {
            movePrintWin({x, 0}, title._text);
        }
        
        else
        {
            movePrintWin({x, _xy._y}, title._text);
        }
    }

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

