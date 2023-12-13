
#include "Config.hpp"
#include "StyleWindow.hpp"
#include <Window.hpp>
#include <ControlKeyboard.hpp>



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
    

    const auto fPrintInWindowText = [&win]()
    {
        win.movePrintWin({0, 0}, "kdfl");
    };

    win.eventKeyboard(fPrintInWindowText, 10);

    std::pair te = win.drawWall(true, 10);

    for (size_t i = 0; i < te.first.size(); i++)
    {
        win.movePrintWin({convertTypeData<short>(i), 0}, te.first[i]);
    }

    win.movePrintWin({0, 1}, "%d", convertTypeData<int>(te.first.size()));

    win.getCh();

    win.close();

    return 0;
}