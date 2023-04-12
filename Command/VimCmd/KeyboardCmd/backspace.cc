#include "backspace.h"

void Backspace::execute(Model &editor) const {
    int lineNum = editor.y();
    int x = editor.x();

    if (x > 0) {
        if (!editor.replacingText()) editor.eraseChar(lineNum, x);
        editor.step(0, -1);
    } else if (lineNum > 0){
        std::string line = editor.getLine(lineNum);
        int aboveLineLen = editor.getLine(lineNum - 1).length();
        if (editor.replacingText()) {
            editor.move(lineNum - 1, aboveLineLen);
        } else {
            editor.getLine(lineNum - 1).append(line);

            editor.removeLine(lineNum);
            editor.move(lineNum - 1, aboveLineLen);
        }
    }
}

 bool Backspace::changesState() const { return true; }
 