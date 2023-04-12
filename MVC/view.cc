#include "view.h"

// do nothing by default if doesn't have these methods
void View::printStatusBarMsg(const std::string &msg) {}
void View::printStatusBarErr(const std::string &err) {} 
int View::windowHeight() { return 0; }
int View::windowWidth() { return 0; }