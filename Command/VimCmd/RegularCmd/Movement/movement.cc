#include "movement.h"

Movement::~Movement() {}

/**- h -**/
void ToLeft::executeOnce(Model &editor) const {
    editor.step(0, -1);
}

/**- l -**/
void ToRight::executeOnce(Model &editor) const {
    editor.step(0, 1);
}

/**- k -**/
void ToPrevLine::executeOnce(Model &editor) const {
    editor.step(-1, 0);
}

/**- j -**/
void ToNextLine::executeOnce(Model &editor) const {
    editor.step(1, 0);
}

/**- 0 -**/
void ToFirstChar::executeOnce(Model &editor) const {
    editor.move(editor.y(), 0);
}

/**- ^ -**/
void ToFirstNonBlankChar::executeOnce(Model &editor) const {
    std::string &line = editor.getLine(editor.y());
    
    int len = line.length();
    for (int c = 0; c < len; c++) {
        if (line[c] != ' ' && line[c] != '\t') {
            editor.move(editor.y(), c);
            break;
        }
    }
}

/**- $ -**/
void ToLastChar::executeOnce(Model &editor) const {
    std::string &line = editor.getLine(editor.y());
    editor.move(editor.y(), line.length());
}

// text motions
const static int NO_WORD = -1;

/**- b -**/
int findPrevLineWord(Model &vim, int lineNum, int c) {
    std::string &line = vim.getLine(lineNum);

    for (--c; c >= 0; --c) {
        if (line[c] != ' ') {
            while (line[c - 1] != ' ') c -= 1;
            vim.move(lineNum, c);
            return c;
        }
    } return NO_WORD;
}

void ToPrevWord::executeOnce(Model &editor) const {
    if (findPrevLineWord(editor, editor.y(), editor.x()) != NO_WORD) return; // check first line
    for (int l = editor.y() - 1; l >= 0; --l) {
        if (findPrevLineWord(editor, l, editor.lineLength(l)) != NO_WORD) return; // check subsequent lines
    }
    // if no word found, move to file end
    editor.move(0,0);
}

/**- w -**/
int findNextLineWord(Model &vim, int lineNum, int c) {
    std::string &line = vim.getLine(lineNum);

    for (; c < line.length(); ++c) {
        if ((c == 0 || line[c-1] == ' ') && line[c] != ' ') {
            vim.move(lineNum, c);
            return c;
        }
    } return NO_WORD;
}
void ToNextWord::executeOnce(Model &editor) const {
    if (findNextLineWord(editor, editor.y(), editor.x() + 1) != NO_WORD) return; // check first line
    for (int l = editor.y() + 1; l < editor.lineCount(); ++l) {
        if (findNextLineWord(editor, l, 0) != NO_WORD) return; // check subsequent lines
    }
    // if no word found, move to file end
    editor.move(editor.lineCount()-1, 0);
    editor.step(0, editor.lineLength(editor.y()));
}


HasCharField::~HasCharField() {}

/**- F -**/
void ToPrevChar::executeOnce(Model &editor) const {
    std::string &line = editor.getLine(editor.y());

    for (int i = editor.x() - 1; i >= 0; --i) {
        if (line[i] == c) {
            editor.move(editor.y(), i);
            break;
        }
    }
}

/**- f -**/
void ToNextChar::executeOnce(Model &editor) const {
    std::string &line = editor.getLine(editor.y());
    int len = line.length();

    for (int i = editor.x() + 1; i < len; ++i) {
        if (line[i] == c) {
            editor.move(editor.y(), i);
            break;
        }
    }
}
