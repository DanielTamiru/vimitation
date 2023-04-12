#ifndef CURSESVIEW_H
#define CURSESVIEW_H

#include "view.h"
#include "vim.h"


#include "../Ncurses/mycurses.h"

class WindowTooSmall{};

class CursesView: public View {
    Ncurses *ncurses;
    Vim &vim;
    int top;
    int left;

    public:
        CursesView(Vim &v, Ncurses *ncurses);
        ~CursesView() override;

        void update() override;
        void displayView() override;
        void printStatusBarMsg(const std::string &msg) override;
        void printStatusBarErr(const std::string &err) override;

        int windowHeight() override;
        int windowWidth() override;
        int windowTop(); // relative the file lines
        int windowBottom(); // relative the file lines
    private:
        int windowLeft(); // relative the file lines
        int windowRight(); // relative the file lines
        int cursesY();
        int cursesX();
        void scrollIfOffScreen();
        void updateLines();
        void printTildes(int font);
        void printCoordinates(int font);
};

#endif
