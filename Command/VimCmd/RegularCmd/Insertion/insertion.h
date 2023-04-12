#ifndef INSERTION_H
#define INSERTION_H

#include "../regularcmd.h"

class Insertion: public RegularCmd {
    public:
        virtual ~Insertion() = 0;
};

/**- i -**/
class InsertLeft: public Insertion {
    void executeOnce(Model &editor) const override;
};

/**- a -**/
class InsertRight: public Insertion {
    void executeOnce(Model &editor) const override;
};

/**- I -**/
class InsertLineStart: public Insertion { 
    void executeOnce(Model &editor) const override;
};

/**- A -**/
class InsertLineEnd: public Insertion { 
    void executeOnce(Model &editor) const override;
};

/**- o -**/
class InsertLineBelow: public Insertion { 
    void executeOnce(Model &editor) const override;
};

/**- O -**/
class InsertLineAbove: public Insertion { 
    void executeOnce(Model &editor) const override;
};


/**- R -**/
class Replace: public Insertion { 
    void executeOnce(Model &editor) const override;
};

#endif
