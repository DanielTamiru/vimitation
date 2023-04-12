#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../regularcmd.h"

class Movement: public RegularCmd {
    public:
        virtual ~Movement() = 0;
};

// ----------------------------

/**- h -**/
class ToLeft: public Movement {
    void executeOnce(Model &editor) const override;
};

/**- l -**/
class ToRight: public Movement {
    void executeOnce(Model &editor) const override;
};

/**- k -**/
class ToPrevLine: public Movement { 
    void executeOnce(Model &editor) const override;
};

/**- j -**/
class ToNextLine: public Movement { 
    void executeOnce(Model &editor) const override;
};

/**- 0 -**/
class ToFirstChar: public Movement {
    void executeOnce(Model &editor) const override;
};

/**- ^ -**/
class ToFirstNonBlankChar: public Movement {
    void executeOnce(Model &editor) const override;
};

/**- $ -**/
class ToLastChar: public Movement {
    void executeOnce(Model &editor) const override;
};

/**- b -**/
class ToPrevWord: public Movement {
    void executeOnce(Model &editor) const override;
};

/**- w -**/
class ToNextWord: public Movement {
    void executeOnce(Model &editor) const override;
};


class HasCharField: public Movement {
    public :
        char c;
         virtual ~HasCharField() = 0;
};

/**- F -**/
class ToPrevChar: public HasCharField {
    void executeOnce(Model &editor) const override; // keep track of last one
};

/**- f -**/
class ToNextChar: public HasCharField {
    void executeOnce(Model &editor) const override; // keep track of last one
};

#endif
