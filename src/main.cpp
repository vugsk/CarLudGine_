
#include <Window>

using namespace clg_cursescpp;

class MainWin : public Window
{
    public:
        MainWin(PairNum<int> xy, PairNum<int> lw, TextXY title = NULL_TEXT_XY)
            : Window(xy, lw, title) {}

};

int main()
{
    initScreen();

    MainWin win({50, 10}, {25, 5});

    win.movePrintWin({10, 5}, "text");

    return 0;
}