#ifndef VIMCMD_H
#define VIMCMD_H

#include "../command.h"
#include "../../MVC/model.h"

class VimCmd: public Cmd {
    public:
        virtual ~VimCmd() = 0;
};

#endif


