#include "mycurses.h"

Ncurses::Ncurses() {
    initscr();
    keypad(stdscr, TRUE);
    raw();
    noecho();
    start_color(); 
    use_default_colors();
}


void Ncurses::SetColorPair(int id, int text, int background) {
    init_pair(id, text, background);
}    

void Ncurses::startAttribute(int id) {
    attron(COLOR_PAIR(id));
}

void Ncurses::stopAttribute(int id) {
    attroff(COLOR_PAIR(id));
}

int Ncurses::getCharacter() {
    return getch();
}

void Ncurses::addCharacter(int c) {
    addch(c);
}

void Ncurses::addString(const std::string &s) {
    addstr(s.c_str());
}

void Ncurses::clearScreen() {
    clear();
}

void Ncurses::refreshScreen() {
    refresh();
}

void Ncurses::clearLine(int lineNum) {
    int y, x;           
    getyx(stdscr, y, x);
    move(lineNum, 0);         
    clrtoeol();          
    move(y, x);
}

void Ncurses::curMove(int y, int x) {
    move(y, x);
}

int Ncurses::yPosn() {
    int y, x;           
    getyx(stdscr, y, x);
    return y;
}

int Ncurses::xPosn() {
    int y, x;           
    getyx(stdscr, y, x);
    return x;
}

int Ncurses::windowWidth() {
    int h, w;
    getmaxyx(stdscr, h, w);
    return w;
}

int Ncurses::windowHeight() {
    int h, w;
    getmaxyx(stdscr, h, w);
    if (h > 0) --h;
    return h;
}
