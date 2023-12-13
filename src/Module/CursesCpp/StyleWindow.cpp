
#include "StyleWindow.hpp"

#include "IWindow.hpp"
#include <algorithm>
#include <cstddef>
#include <curses.h>
#include <functional>
#include <utility>
#include <vector>


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

const std::pair<const std::vector<const char*>&, const bool>&
clg_cursescpp::StyleWindow::drawWall(const bool& isHorizontalOrVertical, const size_t size)
{
    std::vector<const char*> vec(size);

    auto est = [&vec, isHorizontalOrVertical, size](
        const std::pair<const char*, const char*>& pair) 
    {
        if (WALL_TYPES[0] == pair)
        {
            for(size_t i = 1; i < size-1; i++)
            {
                if (isHorizontalOrVertical)
                    vec[i] = pair.first;
                else
                    vec[i] = pair.second;
            }
        }

        // if (isHorizontalOrVertical)
        // {
        //   if (WALL_TYPES[1] == pair)
        //     vec[0] = pair.first;
        //   else
        //     vec[0] = pair.second;
        // }
        // else
        // {
        //   if (WALL_TYPES[2] == pair)
        //     vec[S-1] = pair.first;
        //   else
        //     vec[S-1] = pair.second;
        // }
    };

    std::for_each_n(WALL_TYPES.begin(), size, est); 

    return std::make_pair(vec, isHorizontalOrVertical);
}

// void clg_cursescpp::StyleWindow::drawWall(
//     std::vector<const char*>& vec, const bool isHorizontalOrVertical)
// {
//     auto est = [&vec, &isHorizontalOrVertical](
//         const std::pair<const char*, const char*>& pair) 
//     {
//         if (WALL_TYPES[0] == pair)
//         {
//             for(size_t i = 1; i < S-1; i++)
//             {
//                 if (isHorizontalOrVertical)
//                     vec[i] = pair.first;
//                 else
//                     vec[i] = pair.second;
//             }
//         }

//         if (isHorizontalOrVertical)
//         {
//             if (WALL_TYPES[1] == pair)
//                 vec[0] = pair.first;
//             else
//                 vec[0] = pair.second;
//         }
//         else
//         {
//             if (WALL_TYPES[2] == pair)
//                 vec[S-1] = pair.first;
//             else
//                 vec[S-1] = pair.second;
//         }
//     };

//     std::for_each(WALL_TYPES.begin(), WALL_TYPES.end(), est);
    
    
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
// }


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
