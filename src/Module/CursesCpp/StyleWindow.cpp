
#include "StyleWindow.hpp"
#include "IWindow.hpp"

const char clg_cursescpp::SQUARE_BRACKET_LEFT = '[';
const char clg_cursescpp::SQUARE_BRACKET_RIGHT = ']';

const std::vector<std::pair<const char*, const char*>> clg_cursescpp::WALL_TYPES = {
    {"│", "─"},
    {"┬", "├"},
    {"┴", "┤"}
};


bool clg_cursescpp::StyleWindow::getIsHasColor() const
{
    return _isHasColor;
}

void clg_cursescpp::StyleWindow::generateWall(
    const bool is_horizontal_or_vertical,
    std::vector<const char*>& vec_simbols, const size_t size)
{

    if (size > 0)
    {
        vec_simbols.resize(size);
    }

    auto est = [&vec_simbols, is_horizontal_or_vertical](
        const std::pair<const char*, const char*>& pair) 
    {
        const char* horizontalOrVerticalSimbolWall = 
            is_horizontal_or_vertical? pair.first
                                  : pair.second;

        if (WALL_TYPES[0] == pair)
        {
            for (size_t i = 1; i < vec_simbols.size() - 1; i++)
            {
                vec_simbols[i] = horizontalOrVerticalSimbolWall;
            }
        }
        else if (WALL_TYPES[1] == pair)
        {
            vec_simbols[0] = horizontalOrVerticalSimbolWall;
        }
        else if (WALL_TYPES[2] == pair)
        {
            vec_simbols[vec_simbols.size() - 1] = horizontalOrVerticalSimbolWall;
        }
    };

    std::for_each(WALL_TYPES.begin(), WALL_TYPES.end(), est); 

}

void clg_cursescpp::StyleWindow::drawWall(const size_t lenght, 
    const bool is_horizontal_or_vertical,
    const std::pair<short, short>& where_will_starting_wall) const
{
    std::vector<const char*> wallCh(lenght);
    generateWall(is_horizontal_or_vertical, wallCh);

    for (auto i = 0; i < lenght; i++)
    {
        if (is_horizontal_or_vertical)
        {
            _mWin->movePrintWin({where_will_starting_wall.first - 1,
                i + where_will_starting_wall.second - 1}, wallCh[i]);
        }
        else
        {
            _mWin->movePrintWin({i + where_will_starting_wall.first - 1,
                where_will_starting_wall.second - 1}, wallCh[i]);
        }
    };
}


void clg_cursescpp::StyleWindow::headerWindow(const char* text) const
{
    int x = (ConvertTypeData<int>(_mWin->getXY().first) / 2) -
        (ConvertTypeData<int>(wcslen(converterCharInWchar(text))));
    _mWin->movePrintWin({x, 0}, "%c %s %c",
        SQUARE_BRACKET_LEFT, text, SQUARE_BRACKET_RIGHT);
}


void clg_cursescpp::StyleWindow::clear() const
    { ::clg_cursescpp::wclear(_mWin->getWindow()); }

void clg_cursescpp::StyleWindow::clear(const std::pair<short, short>& begin_xy, 
    const std::pair<short, short>& end_xy) const
{
    for (short i = begin_xy.first; i < end_xy.first; i++)
    {
        for (short j = begin_xy.second; j < end_xy.second; j++)
        {
            _mWin->movePrintWin({i, j}, " ");
        }
    }
}

void clg_cursescpp::StyleWindow::decorateColor(const Color& color, const char ch)
{



}

void clg_cursescpp::StyleWindow::startColor() { ::clg_cursescpp::start_color(); }

//! fix
void clg_cursescpp::StyleWindow::initPairColor(const short pair_number,
    const short foreground, const short background)
{
    ::clg_cursescpp::init_pair(pair_number, foreground, background);
}

//! fix
unsigned long clg_cursescpp::StyleWindow::colorPair(const int pair_number)
{
    return COLOR_PAIR(pair_number);
}

clg_cursescpp::StyleWindow::StyleWindow(IWindow* window)
    : _mWin(window)
{
    #if DEBUG_CURSES_CPP
        PRINT_CONSTRUCTED_DEBUG(STYLE_WINDOW_CL);
    #endif
}

clg_cursescpp::StyleWindow::~StyleWindow()
{
    #if DEBUG_CURSES_CPP
        PRINT_DESTRUCTED_DEBUG(STYLE_WINDOW_CL);
    #endif
}
