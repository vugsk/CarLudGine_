
#include <Window>



int main()
{
    initscr();
    clg_cursescpp::Window win;
    win.box(0, 0);
    win.update();
    win.movePrintWin({10, 5}, "text");
    win.getChar();
    win.refresh();

    clg_cursescpp::Window* test = win.createWindow(
        {50, 10},
        {(win.getX()/2)-25, (win.getY()/2)-5}
    );

    test->box(0, 0);
    test->update();
    test->getChar();

    return 0;
}