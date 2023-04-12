#ifndef KEYBOARDCMD_H
#define KEYBOARDCMD_H

#include "../vimcmd.h"
#include <string>

class KeyboardCmd: public VimCmd {
    public:
        virtual ~KeyboardCmd() = 0;
};

#endif
