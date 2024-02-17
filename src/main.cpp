

#include <ControlKeyboard.hpp>
#include <iostream>
#include <Window.hpp>


int main()
{
    clg_cursescpp::initScreen(true);

    constexpr std::pair<unsigned, unsigned> xy   = {50, 5};
    constexpr std::pair<unsigned, unsigned> size = {50, 5};

    clg_cursescpp::Window window(xy, size);
    const clg_cursescpp::ControlKeyboard ck(window, true, 0);

    window.printWin("text");
    int io = ck.getCh();

    return 0;
}
