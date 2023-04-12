#include "newline.h"

void Newline::execute(Model &editor) const {
    int lineNum = editor.y();
    int x = editor.x();

    // remove line tail
    std::string &line = editor.getLine(lineNum);

    std::string tail = line.substr(x);
    line = line.substr(0, x);

    // insert line tail below
    editor.insertLine(lineNum + 1, tail);

    editor.move(lineNum + 1, 0);
}

bool Newline::changesState() const { return true; }
