#include "insertion.h"

Insertion::~Insertion() {}

/**- i -**/
void InsertLeft::executeOnce(Model &editor) const {
    editor.startInsertMode();
}


/**- a -**/
void InsertRight::executeOnce(Model &editor) const {
    editor.startInsertMode();
    editor.step(0, 1);
}

/**- I -**/
void InsertLineStart::executeOnce(Model &editor) const {
    editor.startInsertMode();
    editor.move(editor.y(), 0);
}

/**- A -**/
void InsertLineEnd::executeOnce(Model &editor) const {
    editor.startInsertMode();
    editor.move(editor.y(), editor.lineLength(editor.y()));
}

/**- o -**/
void InsertLineBelow::executeOnce(Model &editor) const {
    editor.startInsertMode();
    
    int lineNum = editor.y();
    int x = editor.x();
    std::string &line = editor.getLine(lineNum);

    // insert line tail below
    editor.insertLine(lineNum + 1, std::string());
    editor.move(lineNum + 1, 0);
}

/**- O -**/
void InsertLineAbove::executeOnce(Model &editor) const {
    editor.startInsertMode();

    int lineNum = editor.y();
    int x = editor.x();
    std::string &line = editor.getLine(lineNum);

    // insert line tail below
    editor.insertLine(lineNum, std::string());
    editor.move(lineNum, 0);
}

/**- R -**/
void Replace::executeOnce(Model &editor) const {
    editor.startReplaceMode();
}

