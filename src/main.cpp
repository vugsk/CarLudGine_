
#include "Config.hpp"
#include "StyleWindow.hpp"
#include <Window.hpp>
#include <ControlKeyboard.hpp>
#include <functional>
#include <utility>
#include <vector>



using namespace clg_cursescpp;

class MainWin : public Window, public ControlKeyboard, public StyleWindow
{
    public:
        MainWin(const std::pair<int, int>& xy, 
                const std::pair<int, int>& lw)
            : Window(xy, lw)
            , ControlKeyboard(getWindow(), true, 0)
            , StyleWindow(getWindow(), getXY()) {}

        ~MainWin() {}

};

int main()
{
    initScreen(true);

    MainWin win({50, 10}, {25, 5});
    

    // const auto fPrintInWindowText = [&win]()
    // {
    //     win.movePrintWin({0, 0}, "kdfl");
    // };

    // win.eventKeyboard(fPrintInWindowText, 10);


    win.drawWall(10, false, 
        std::make_pair<short, short>(5, 1), win);
    

    win.getCh();

    win.close();

    return 0;
}