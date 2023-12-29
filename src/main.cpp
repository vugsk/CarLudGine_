
#include "StyleWindow.hpp"
#include <ControlKeyboard.hpp>
#include <Window.hpp>
#include <curses.h>
#include <iostream>


using namespace clg_cursescpp;

class MainWin : public Window
              , public ControlKeyboard
              , public StyleWindow
{
    public:
        MainWin(const std::pair<int, int>& xy, 
                const std::pair<int, int>& lw)
            : Window(xy, lw)
            , ControlKeyboard(getWindow(), true, 0)
            , StyleWindow(this)
        {
            startColor();
        }

        // void test()
        // {
        //     initPairColor(1, Color::BLACK, Color::WHITE);
        //     wbkgd(getWindow(), colorPair(1));
        // }

         ~MainWin() {}

};

int main()
{
    initScreen(true);

    // init_pair(1, Color::BLUE, Color::RED);
    // bkgd(COLOR_PAIR(1));

    MainWin win({50, 10}, {25, 5});

    // win.test();

    // win.decorateColor(Color::BLACK, 'o');

    // const auto fPrintInWindowText = [&win]()
    // {
    //     win.movePrintWin({0, 0}, "kdfl");
    // };

    // win.eventKeyboard(fPrintInWindowText, 10);



    // win.drawWall(10, true, {10, 1});
    
    // win.headerWindow("loihoi");



    win.getCh();

    win.close();

    return 0;
}