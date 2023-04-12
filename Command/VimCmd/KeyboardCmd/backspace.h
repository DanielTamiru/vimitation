#ifndef BACKSPACECMD_H
#define BACKSPACECMD_H

#include "keyboardcmd.h"

class Backspace: public KeyboardCmd {
    public:
        void execute(Model &editor) const override;
    bool changesState() const override;
};

#endif
