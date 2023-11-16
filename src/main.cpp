
#include <curses.h>
#include <iostream>

#include <Window>

class NewWin : public clg_cursescpp::Window {
    public:
        NewWin() {
            
        }

        void update() override {
            std::cout << "dkjfl\n";
        }
};

int main()
{
    initscr();
    NewWin win;
    win.box(0, 0);
    win.refresh();
    win.update();

    std::cout << clg_cursescpp::Window::SCREEN_XY._x << '\n';

    win.getChar();
    win.refresh();

    clg_cursescpp::Window* test = new NewWin();

    test = win.createWindow({50, 10}, {
        (clg_cursescpp::Window::SCREEN_XY._x/2)-25, 
        (clg_cursescpp::Window::SCREEN_XY._y/2)-5
    });

    test->box(0, 0);
    test->refresh();
    test->update();
    test->getChar();
    test->close();

    win.close();

    return 0;
}