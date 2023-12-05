
#include <Window.hpp>
#include <ControlKeyboard.hpp>


using namespace clg_cursescpp;

class MainWin : public Window, public ControlKeyboard
{
    public:
        MainWin(const std::pair<int, int>& xy, 
                const std::pair<int, int>& lw)
            : Window(xy, lw)
            , ControlKeyboard(getWindow(), true, 0) {}

};



int main()
{
    initScreen(true);

    MainWin win(std::make_pair(50, 10), 
                std::make_pair(25, 5));

    win.eventKeyboard([&win]() {
        win.printWin("kdfl");
    }, 10);

    win.close();

    return 0;
}