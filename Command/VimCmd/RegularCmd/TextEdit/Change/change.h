#ifndef CHANGECMD_H
#define CHANGECMD_H

#include "../textedit.h"

class Change: public TextEdit {
    public:
        virtual ~Change() = 0;
};

class ChangeMotion: public Change {
    public:
        void executeOnce(Model &vim) const override;
};

class ChangeChars: public Change {
    public:
        void executeOnce(Model &vim) const override;
};

class ChangeLines: public Change {
    public:
        void executeOnce(Model &vim) const override;
};

//------------

class ChangeHasCharField: public Change {
    public :
        char c;
         virtual ~ChangeHasCharField() = 0;
};

class ReplaceWithChars: public ChangeHasCharField {
    public:
        void executeOnce(Model &vim) const override;
};

#endif
