#ifndef ESCAPECMD_H
#define ESCAPECMD_H

#include "keyboardcmd.h"

class Escape: public KeyboardCmd {
    public:
        void execute(Model &editor) const override;
};


#endif
