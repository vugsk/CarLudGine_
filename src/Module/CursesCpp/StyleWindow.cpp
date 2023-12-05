
#include "StyleWindow.hpp"

#include "IWindow.hpp"



const bool clg_cursescpp::StyleWindow::getIsHasColor()
{
    return isHasColor;
}





clg_cursescpp::StyleWindow::StyleWindow(const clg_cursescpp::IWindow& window)
    : win(window.getWindow()) {}

clg_cursescpp::StyleWindow::StyleWindow(WINDOW* window)
{
    if (!window)
    {
        win = window;
    }
    else
    {
        win = nullptr;
    }

}

clg_cursescpp::StyleWindow::~StyleWindow()
{

}