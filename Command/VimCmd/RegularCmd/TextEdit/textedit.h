#ifndef MOVEEDIT_H
#define MOVEEDIT_H

#include "../Movement/movement.h"
#include "../regularcmd.h"

class TextEdit: public RegularCmd{
    public:
       Movement *motion;
       TextEdit();
       virtual ~TextEdit();
};



#endif
