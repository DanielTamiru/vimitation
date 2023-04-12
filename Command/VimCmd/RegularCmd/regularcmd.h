#ifndef REGULARCMD_H
#define REGULARCMD_H

#include "../vimcmd.h"

class RegularCmd: public VimCmd {
    virtual void preExecute(Model &editor) const;
    virtual void executeOnce(Model &editor) const = 0;
    virtual void postExecute(Model &editor) const;
    public:
        int multiplier;

        RegularCmd();
        void execute(Model &editor) const override;
};
#endif
