#ifndef VIEW_H
#define VIEW_H

#include <string>



class View {
    public:
        virtual ~View() = default;
        virtual void update() = 0;
        virtual void displayView() = 0;
        virtual void printStatusBarMsg(const std::string &msg);
        virtual void printStatusBarErr(const std::string &err);
        
        virtual int windowHeight();
        virtual int windowWidth();
};

#endif
