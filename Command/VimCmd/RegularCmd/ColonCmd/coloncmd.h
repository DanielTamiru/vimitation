#ifndef FILECMD_H
#define FILECMD_H

#include "../regularcmd.h"

class ColonCmd: public RegularCmd{
    public:
        std::string file;
        virtual ~ColonCmd() = 0;
};

class Write: public ColonCmd {
    void executeOnce(Model &vim) const override;
};  

class Read: public ColonCmd {
    bool changesState() const override;
    void executeOnce(Model &vim) const override;
};  

class Quit: public ColonCmd {
    void executeOnce(Model &vim) const override;
};  

class ForceQuit: public ColonCmd {
    void executeOnce(Model &vim) const override;
};  

class WriteQuit: public ColonCmd {
    void executeOnce(Model &vim) const override;
};  

class toLineNumber: public ColonCmd {
    void executeOnce(Model &vim) const override;
};  

#endif
