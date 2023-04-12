#ifndef CHARACTERCMD_H
#define CHARACTERCMD_H

#include "keyboardcmd.h"

class Character: public KeyboardCmd {
    public:
        char c;
        Character(char c);
        void execute(Model &editor) const override;

        bool changesState() const override;
};

#endif
