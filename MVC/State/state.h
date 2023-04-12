#ifndef STATE_H
#define STATE_H
//vim, model, view, cursesview
#include <string>
#include <fstream>
#include <vector>


class State {
    public:
        std::string filePath;
        bool didChange;
        bool newFile;

        int curX;
        int curY;
        
        State();
        State(const std::string &file);
        virtual ~State() = 0;
};

#endif
