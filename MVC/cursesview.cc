#include "cursesview.h"
#include <string>
#include <vector>

const static int OUT_OF_VIEW = -1;

const static int DEFAULT = -1;
const static int CYAN = 1;
const static int YELLOW = 2;
const static int ERROR_RED = 3;

CursesView::CursesView(Vim &v, Ncurses *ncurses): vim{v}, ncurses{ncurses}, top{0}, left{0} { 
    if (windowHeight() <= 0 || windowWidth() < 15) throw WindowTooSmall{};

    ncurses->SetColorPair(CYAN, COLOR_CYAN, DEFAULT);
    ncurses->SetColorPair(YELLOW, COLOR_YELLOW, DEFAULT);
    ncurses->SetColorPair(ERROR_RED, COLOR_WHITE, COLOR_RED);
}
CursesView::~CursesView() {}


void CursesView::update() {
    ncurses->clearScreen(); // wipe screen
    scrollIfOffScreen(); // scroll
    updateLines(); // print the lines and move the cursor
}

void CursesView::displayView() { 
    ncurses->clearLine(windowHeight());
    if (left == 0) printTildes(CYAN);
    if (vim.insertingText()) printStatusBarMsg("-- INSERT --");
    else if (vim.replacingText()) printStatusBarMsg("-- REPLACE --");
    else printCoordinates(YELLOW);
    ncurses->refreshScreen(); 
} 


inline int CursesView::windowHeight() { return ncurses->windowHeight(); }

inline int CursesView::windowWidth() { return ncurses->windowWidth(); }

inline int CursesView::windowTop() { return top; }

inline int CursesView::windowBottom() { return top + ncurses->windowHeight(); }

inline int CursesView::windowLeft() { return left; }

inline int CursesView::windowRight() { return left + ncurses->windowWidth(); }

inline int CursesView::cursesY() { return vim.y() - top; }

inline int CursesView::cursesX() { return vim.x() - left; }

void CursesView::scrollIfOffScreen() {
    if (vim.y() >= windowBottom()) top += vim.y() - windowBottom() + 1;
    else if (vim.y() < top) top = vim.y();

    if (vim.x() >= windowRight()) left += vim.x() - windowRight() + 1;
    else if (vim.x() < left) left = vim.x();
}

inline int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

void CursesView::updateLines() {
    for (int l = top; l < vim.lineCount() && l < windowBottom(); ++l) {
        ncurses->curMove(l - top, 0);
        std::string line = vim.getLine(l);
        
        if (line.length() > left) {
            int lineEnd = min(line.length() - left, windowRight() - left);
            addstr((line.substr(left, lineEnd)).c_str());
        } 
    }
    ncurses->curMove(cursesY(), cursesX());
}

void CursesView::printTildes(int font) {
    int i = ncurses->windowHeight(), lastFileLine = vim.lineCount();

    int curY = ncurses->yPosn(), curX = ncurses->xPosn();

    ncurses->startAttribute(font);
    for (int l = windowBottom()-1; l >= lastFileLine && l >= top; --l) {
        ncurses->curMove(--i, 0);
        ncurses->addCharacter('~');
    }
    ncurses->stopAttribute(font);

    ncurses->curMove(curY, curX); // reset the cursor
}

void CursesView::printStatusBarMsg(const std::string &msg) {
    int curY = ncurses->yPosn(), curX = ncurses->xPosn();
    ncurses->clearLine(windowHeight());
    ncurses->curMove(ncurses->windowHeight(), 0);

    ncurses->startAttribute(YELLOW);
    if (windowWidth() > msg.length() + 1) ncurses->addString(msg);
    ncurses->stopAttribute(YELLOW);
    ncurses->curMove(curY, curX); // reset the cursor

    printCoordinates(YELLOW);
    ncurses->refreshScreen();
}

void CursesView::printStatusBarErr(const std::string &err) {
    int curY = ncurses->yPosn(), curX = ncurses->xPosn();
    ncurses->clearLine(windowHeight());
    ncurses->curMove(ncurses->windowHeight(), 0);

    ncurses->startAttribute(ERROR_RED);
    if (windowWidth() > err.length() + 1) ncurses->addString(err);
    ncurses->stopAttribute(ERROR_RED);
    ncurses->curMove(curY, curX); // reset the cursor

    printCoordinates(YELLOW);
    ncurses->refreshScreen();
}


void CursesView::printCoordinates(int font) {
    int curY = ncurses->yPosn(), curX = ncurses->xPosn();
    int x = vim.x() + 1;
    int y = vim.y() + 1;
    std::string cursorCoordinates = std::to_string(x) + "," + std::to_string(y);
    int printPosn = windowWidth() - cursorCoordinates.length() - 5;
    if (printPosn > 50) { // 50 is resonable amount of space to print the status bar msg
        ncurses->curMove(windowHeight(), printPosn);
        ncurses->startAttribute(font);
        ncurses->addString(cursorCoordinates);
        ncurses->stopAttribute(font);
    }

    ncurses->curMove(curY, curX); // reset the cursor
}
