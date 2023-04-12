#ifndef STATUS_BAR
#define STATUS_BAR

#include <string>

class StatusBar {
    public:
        virtual void printError(std::string s) = 0;
        virtual void printMsg(std::string s) = 0;
};

#endif
