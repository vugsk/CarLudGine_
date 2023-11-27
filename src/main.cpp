
#include <ControlKeyboardAndMaus>
#include <Window>

#include <iostream>


using namespace clg_cursescpp;

class MainWin : public Window, public ControlKeyboard
{
    public:
        MainWin(PairNum<int> xy, PairNum<int> lw)
            : Window(xy, lw)
        {
            curs(0);
            echo(true);
        }
    
    protected:
        pWIN getWin() override {
            return getWindow();
        }



};

void test(MainWin* win) {

    // std::cout << win.getX() << "dksfla\n";

    
    win->printWin("jdfl");
    

}

int main()
{

    initScreen(true);

    MainWin *win = new MainWin({50, 10}, {25, 5});

    win->eventKeyboard(std::bind(test, win), 10);

    win->close();

    return 0;
}