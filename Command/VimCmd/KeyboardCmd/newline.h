#ifndef ENTERCMD_H
#define ENTERCMD_H

#include "keyboardcmd.h"

class Newline: public KeyboardCmd {
    public:
        void execute(Model &editor) const override;
    bool changesState() const override;
};

#endif
