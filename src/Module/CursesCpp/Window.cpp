
#include "Window"


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


/*
    Private
*/


const clg_cursescpp::PairNum<int> clg_cursescpp::Window::NULL_XY = {0, 0};

inline void clg_cursescpp::Window::print(const char *text, va_list args, 
    clg_cursescpp::PairNum<int> xy)
{
    wmove(_win, xy._y, xy._x);
    vw_printw(_win, text, args);
    wrefresh(_win);
}


/*
    Public
*/

short clg_cursescpp::Window::getX() { return _xy._x; }
short clg_cursescpp::Window::getY() { return _xy._y; }

int clg_cursescpp::Window::getMaxX() { return getmaxx(_win); }
int clg_cursescpp::Window::getMaxY() { return getmaxy(_win); }

clg_cursescpp::PairNum<int> clg_cursescpp::Window::getMaxXY()
{ 
    return { 
        getMaxX(), 
        getMaxY() 
    };
}

int clg_cursescpp::Window::getChar() { return wgetch(_win); }
void clg_cursescpp::Window::box(const unsigned a, const unsigned b) { ::box(_win, a, b); }
void clg_cursescpp::Window::close() { delwin(_win); }
void clg_cursescpp::Window::refresh() { wrefresh(_win); }


void clg_cursescpp::Window::movePrintWin(clg_cursescpp::PairNum<int> xy, 
    const char* text, ...)
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


template<typename F>
void clg_cursescpp::Window::textSelection(
    size_t sizeTextArrayForMenu,
    std::function<F> updateFunc)
{
    for (size_t i = 0; i < sizeTextArrayForMenu; i++) updateFunc();
}

template<typename F1, typename F2>
void clg_cursescpp::Window::textSelectionTable(
    size_t sizeFirstArray, size_t sizeSecondArray,
    std::function<F1> updateFuncRunInLoopFirstArray,
    std::function<F2> updateFuncRunInLoopSecondArray)
{
    for (size_t i = 0; i < sizeFirstArray; i++)
    {
        textSelection(sizeSecondArray, updateFuncRunInLoopSecondArray);
        updateFuncRunInLoopFirstArray();
    }
}


clg_cursescpp::Window* clg_cursescpp::Window::createWindow(
    const PairNum<int> xy,
    const PairNum<int> widthAndLength)
{
    return new Window(convertStructPairNum<short>(xy), 
        newwin(xy._y, xy._x, widthAndLength._y, widthAndLength._x));
}


void clg_cursescpp::Window::textSelectionTable() {}
void clg_cursescpp::Window::textSelection() {}
void clg_cursescpp::Window::update() {}


clg_cursescpp::Window::Window() 
    : _win(stdscr)
    , _xy(convertStructPairNum<short>(getMaxXY()))
{

}

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

