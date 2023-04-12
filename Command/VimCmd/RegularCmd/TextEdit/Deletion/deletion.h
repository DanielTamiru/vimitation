#ifndef DELCMD_H
#define DELCMD_H

#include "../textedit.h"

class Delete: public TextEdit {
    public:
        virtual ~Delete() = 0;
};

class DelMotion: public Delete {
    public:
        void executeOnce(Model &vim) const override;
};

class DelLines: public Delete {
    public:
        void executeOnce(Model &vim) const override;
};

class DelUnderAfter: public Delete {
    public:
        void executeOnce(Model &vim) const override;
};

class DelCharBefore: public Delete {
    public:
        void executeOnce(Model &vim) const override;
};

class DelJoin: public Delete {
    public:
        void executeOnce(Model &vim) const override;
};
#endif
