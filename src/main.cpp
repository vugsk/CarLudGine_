
#include <ControlKeyboard.hpp>
#include <Window.hpp>

using namespace clg_cursescpp;

class MainWin : public Window, public ControlKeyboard
{
    public:
        MainWin(PairNum<int> xy, PairNum<int> lw)
            : Window(xy, lw)
            , ControlKeyboard(getWindow(), true, 0) {}

};

int main()
{
    initScreen(true);

    MainWin win({50, 10}, {25, 5});

    win.eventKeyboard([&win]() {

        win.printWin("kdfl");
    
    }, 10);

    win.close();

    return 0;
}