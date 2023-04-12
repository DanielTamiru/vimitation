#ifndef MYCURSES_H
#define MYCURSES_H

#include <ncurses.h>
#include <string>

class Ncurses {
    public:
        const int BACKSPACE_KEY = KEY_BACKSPACE;
        Ncurses();

        void SetColorPair(int id, int text, int background);    
        void startAttribute(int id);
        void stopAttribute(int id);

        int getCharacter();
        void addCharacter(int c);
        void addString(const std::string &s);
        void clearScreen();
        void refreshScreen();
        void clearLine(int lineNum);

        void curMove(int y, int x);
        int yPosn();
        int xPosn();
        int windowWidth();
        int windowHeight();
};

#endif
