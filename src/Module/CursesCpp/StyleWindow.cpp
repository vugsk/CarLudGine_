
#include "StyleWindow.hpp"

#include "Config.hpp"
#include "IWindow.hpp"
#include <any>
#include <cstddef>
#include <cstring>
#include <cwchar>
#include <iostream>
#include <utility>


const std::vector<std::pair<const char*, 
    const char*>> clg_cursescpp::WALL_TYPES = {
        std::make_pair("│", "─"),
        std::make_pair("┬", "├"),
        std::make_pair("┴", "┤")
};


const bool clg_cursescpp::StyleWindow::getIsHasColor()
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
    const std::pair<short, short>& whereWillStartingWall)
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


void clg_cursescpp::StyleWindow::headerWindow(const char* text)
{
    int x = (_mWin->getXY().first/2)-(wcslen(converterCharInWchar(text)));

    _mWin->movePrintWin({x, 0}, "[ %s ]", text);
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
