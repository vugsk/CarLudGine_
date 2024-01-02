
#include "StyleWindow.hpp"
#include "IWindow.hpp"

const char clg_cursescpp::SKOBKI_LEFT = '[';
const char clg_cursescpp::SKOBKI_RIGHT = ']';

const std::vector<std::pair<const char*, 
    const char*>> clg_cursescpp::WALL_TYPES = {
        std::make_pair("│", "─"),
        std::make_pair("┬", "├"),
        std::make_pair("┴", "┤")
};


bool clg_cursescpp::StyleWindow::getIsHasColor() const
{
    return _isHasColor;
}

void clg_cursescpp::StyleWindow::generateWall(
    const bool isHorizontalOrVertical, 
    std::vector<const char*>& vecSimbols, const size_t size)
{

    if (size > 0) vecSimbols.resize(size);  

    auto est = [&vecSimbols, isHorizontalOrVertical](
        const std::pair<const char*, const char*>& pair) 
    {
        const char* horizontalOrVerticalSimbolWall = 
            isHorizontalOrVertical? pair.first
                                  : pair.second;

        if (WALL_TYPES[0] == pair)
        {
            for (size_t i = 1; i < vecSimbols.size()-1; i++)
            {
                vecSimbols[i] = horizontalOrVerticalSimbolWall;
            }
        }
        else if (WALL_TYPES[1] == pair)
        {
            vecSimbols[0] = horizontalOrVerticalSimbolWall;
        }
        else if (WALL_TYPES[2] == pair)
        {
            vecSimbols[vecSimbols.size()-1] = horizontalOrVerticalSimbolWall;
        }
    };

    std::for_each(WALL_TYPES.begin(), WALL_TYPES.end(), est); 

}

void clg_cursescpp::StyleWindow::drawWall(const size_t lenght, 
    const bool isHorizontalOrVertical,
    const std::pair<short, short>& whereWillStartingWall) const
{
    std::vector<const char*> wallCh(lenght);
    generateWall(isHorizontalOrVertical, wallCh);

    for (int i = 0; i < lenght; i++)
    {
        if (isHorizontalOrVertical)
        {
            _mWin->movePrintWin({whereWillStartingWall.first-1, 
                i+whereWillStartingWall.second-1}, wallCh[i]);
        }
        else
        {
            _mWin->movePrintWin({i+whereWillStartingWall.first-1, 
                whereWillStartingWall.second-1}, wallCh[i]);
        }
    };
}


void clg_cursescpp::StyleWindow::headerWindow(const char* text) const
{
    int x = (convertTypeData<int>(_mWin->getXY().first)/2) -
        (convertTypeData<int>(wcslen(converterCharInWchar(text))));
    _mWin->movePrintWin({x, 0}, "%c %s %c",
        SKOBKI_LEFT, text, SKOBKI_RIGHT);
}


void clg_cursescpp::StyleWindow::clear() const { ::wclear(_mWin->getWindow()); }

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

void clg_cursescpp::StyleWindow::startColor() { ::start_color(); }

//! fix
void clg_cursescpp::StyleWindow::initPairColor(const short pair_number,
    const short foreground, const short background)
{
    ::init_pair(pair_number, foreground, background);
}

//! fix
unsigned long clg_cursescpp::StyleWindow::colorPair(const int pairNumber)
{
    return COLOR_PAIR(pairNumber);
}

clg_cursescpp::StyleWindow::StyleWindow(IWindow* window)
    : _mWin(window)
{
    #if DEBUG
        PRINT_CONSTRUCTED_DEBUG(STYLE_WINDOW_CL);
    #endif
}

clg_cursescpp::StyleWindow::~StyleWindow()
{
    #if DEBUG
        PRINT_DESTRUCTED_DEBUG(STYLE_WINDOW_CL);
    #endif
}
