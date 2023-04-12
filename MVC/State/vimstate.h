#ifndef VIMSTATE_H
#define VIMSTATE_H

#include "state.h"
#include <vector>


class VimState: public State {
    public:
        std::vector<std::string> lines;
        VimState(const std::string &file);
};


#endif
