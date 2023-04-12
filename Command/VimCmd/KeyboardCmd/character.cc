#include "character.h"

Character::Character(char c): c{c} {}

void Character::execute(Model &editor) const {
    int x = editor.x();
    int y = editor.y();
    
    if (c == '\t') {
        std::string tab = "    ";
        editor.getLine(y).insert(x, tab);
        editor.step(0, 4);
    }
    else {
        if (editor.replacingText() && x < editor.lineLength(y)) editor.getLine(y)[x] = c;
        else editor.getLine(y).insert(x, std::string(1, c)); // change to char insert in str
       
        editor.step(0, 1);
    }
    
}

bool Character::changesState() const { return true; }
