
#include "StyleWindow.hpp"
#include <Window.hpp>
#include <ControlKeyboard.hpp>
#include <cstddef>
#include <utility>



using namespace clg_cursescpp;

class MainWin : public Window, public ControlKeyboard, public StyleWindow
{
    public:
        MainWin(const std::pair<int, int>& xy, 
                const std::pair<int, int>& lw)
            : Window(xy, lw)
            , ControlKeyboard(getWindow(), true, 0)
            , StyleWindow(getWindow(), getXY())

        {
            #if DEBUG
                PRINT_CONSTRUCTED_DEBUG("MainWin");
            #endif
        }

        ~MainWin() {
            #if DEBUG
                PRINT_DESTRUCTED_DEBUG("MainWin");
            #endif
        }

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

    std::vector<const char*> vec;

    win.drawWall(vec, true);


    win.close();

    return 0;
}