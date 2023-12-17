
#include "StyleWindow.hpp"
#include <ControlKeyboard.hpp>
#include <Window.hpp>


using namespace clg_cursescpp;

class MainWin : public Window, public ControlKeyboard, public StyleWindow
{
    public:
        MainWin(const std::pair<int, int>& xy, 
                const std::pair<int, int>& lw)
            : Window(xy, lw)
            , ControlKeyboard(getWindow(), true, 0)
            , StyleWindow(this) {}

         ~MainWin() {}

};

void te(int ui)
{}

int main()
{
    initScreen(true);

    MainWin win({50, 10}, {25, 5});
    

    // const auto fPrintInWindowText = [&win]()
    // {
    //     win.movePrintWin({0, 0}, "kdfl");
    // };

    // win.eventKeyboard(fPrintInWindowText, 10);


    win.drawWall(10, true, {10, 1});
    
    win.headerWindow("loihoi");

    win.getCh();

    win.close();

    return 0;
}