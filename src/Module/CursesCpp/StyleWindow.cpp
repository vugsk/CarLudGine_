
#include "StyleWindow.hpp"

#include "IWindow.hpp"
#include <algorithm>
#include <curses.h>
#include <functional>
#include <utility>
#include <vector>


// const char* clg_cursescpp::WALL_Y_PERPENDICULAR        = "│";
// const char* clg_cursescpp::WALL_Y_ANGLE_UNDER_90_DOWN  = "┬"; 
// const char* clg_cursescpp::WALL_Y_ANGLE_UNDER_90_TOP   = "┴";
// const char* clg_cursescpp::WALL_X_IN_PARALLEL          = "─";
// const char* clg_cursescpp::WALL_X_ANGLE_UNDER_90_LEFT  = "├";
// const char* clg_cursescpp::WALL_X_ANGLE_UNDER_90_RIGHT = "┤";

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

//! fix
void test(std::vector<const char*>& vec, const bool isHorizontalOrVertical,
    const std::pair<const char*, const char*>& pair)
{

    if (isHorizontalOrVertical)
    {
        vec.push_back(pair.first);
    }
    else
    {
        vec.push_back(pair.second);
    }

}

void clg_cursescpp::StyleWindow::drawWall(
    std::vector<const char*>& vec, const bool isHorizontalOrVertical)
{

    // auto est = [&vec, &isHorizontalOrVertical](
    //     const std::pair<const char*, const char*>& pair) 
    // {
    //     if (isHorizontalOrVertical)
    //     {
    //         vec.push_back(pair.first);
    //     }
    //     else
    //     {
    //         vec.push_back(pair.second);
    //     }
    // };

    std::for_each(WALL_TYPES.begin(), WALL_TYPES.end(), 
        std::bind(test, vec, isHorizontalOrVertical, std::placeholders::_1));
    
    
    // const char* WALL;
    // const char* WALL_90;
    // const char* WALL_180;

    // int numXOrY;

    // if (isHorizontalOrVertical) 
    // {
        // WALL = WALL_Y_PERPENDICULAR;
        // WALL_90 = WALL_Y_ANGLE_UNDER_90_DOWN;
        // WALL_180 = WALL_Y_ANGLE_UNDER_90_TOP;
        
    //     numXOrY = _xy.second;
    // }
    // else 
    // {
        // WALL = WALL_X_IN_PARALLEL;
        // WALL_90 = WALL_X_ANGLE_UNDER_90_LEFT;
        // WALL_180 = WALL_X_ANGLE_UNDER_90_RIGHT;

        // numXOrY = _xy.first;

        // std::swap(xy.first, xy.second);
        
        // int temp;
        // temp = xy.first;
        // wall_x = wall_y;
        // wall_y = temp;
    // }

    // for (int i = numXOrY - xy.first; i < numXOrY; i++)
    // {
    //     if (i != numXOrY - 1)
    //     {
    //         if (isHorizontalOrVertical) 
    //         {
    //             print(xy.first, i, WALL);
    //         }
    //         else 
    //         {
    //             print(i, xy.second, WALL);
    //         }
    //     }
    // }

    // if (isHorizontalOrVertical)
    // {
    //     print(wall_x, y - wall_y, WALL_90);
    //     print(wall_x, y - 1, WALL_180);
    // } 
    // else
    // {
    //     print(x - wall_x, wall_y, WALL_90);
    //     print(x - 1, wall_y, WALL_180);
    // }
}


clg_cursescpp::StyleWindow::StyleWindow(const clg_cursescpp::IWindow& window)
    : _win(window.getWindow())
    , _xy(window.getXY())
{
    #if DEBUG
        PRINT_CONSTRUCTED_DEBUG(STYLE_WINDOW_CL);
    #endif
}

clg_cursescpp::StyleWindow::StyleWindow(WINDOW* window, 
        const std::pair<short, short>& xy)
    : _win(checkingForWindow(window))
    , _xy(xy)
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
