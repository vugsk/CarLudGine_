
#include <Window>
#include <iostream>

class NewWin: public clg_cursescpp::Window {
    public:
        NewWin(const clg_cursescpp::Window &other)
            : clg_cursescpp::Window(other) {}
        
        void update() override {
            printWin("lol");
        }

        void textSelection() override {
            
        }
    
};

int main()
{
    initscr();
    clg_cursescpp::Window win;
    win.box(0, 0);
    win.update();
    win.movePrintWin({10, 5}, "text");
    win.getChar();
    win.refresh();

    NewWin test(win.createWindow(
        {50, 10},
        {(win.getX()/2)-25, (win.getY()/2)-5}
    ));

    test.box(0, 0);
    test.update();
    test.getChar();

    return 0;
}