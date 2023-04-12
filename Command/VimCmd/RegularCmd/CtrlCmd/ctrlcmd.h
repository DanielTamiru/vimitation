#ifndef CTRLCMD_H
#define CTRLCMD_H

#include "../regularcmd.h"
#include "../../../../MVC/statusbar.h"

class CtrlCmd: public RegularCmd {
    public:
        virtual ~CtrlCmd() = 0;
};

/**- ^u -**/
class ToPrevWLine: public CtrlCmd { 
    void executeOnce(Model &vim) const override;
};

/**- ^d -**/
class ToNextWLine: public CtrlCmd { 
    void executeOnce(Model &vim) const override;
};

/**- ^b -**/
class ToPrevPage: public CtrlCmd {
    void executeOnce(Model &vim) const override;
};

/**- ^f -**/
class ToNextPage: public CtrlCmd {
    void executeOnce(Model &vim) const override;
};


class HasStatusBar: public CtrlCmd {
    public:
        StatusBar* bar;
        virtual ~HasStatusBar() = 0;
};

/**- ^g -**/
class ShowFileName: public HasStatusBar {
    bool printsToScreen() const override;
    void executeOnce(Model &vim) const override;
};

#endif
