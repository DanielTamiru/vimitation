#include "ctrlcmd.h"

CtrlCmd::~CtrlCmd() {}

//-- ^u --//
void ToPrevWLine::executeOnce(Model &editor) const {
    editor.step(-1, 0);
}

//-- ^d --//
void ToNextWLine::executeOnce(Model &editor) const {
    editor.step(1, 0);
}

//-- ^b --//
void ToPrevPage::executeOnce(Model &editor) const {
    int yChange = editor.windowHeight() / 2;
    editor.step(-yChange , 0);
}

//-- ^f --//
void ToNextPage::executeOnce(Model &editor) const {
    int yChange = editor.windowHeight() / 2;
    editor.step(yChange, 0);
}


HasStatusBar::~HasStatusBar() {}

//-- ^g --//
void ShowFileName::executeOnce(Model &editor) const {
    std::string file = editor.getFilePath();
    bar->printMsg(file);
}

bool ShowFileName::printsToScreen() const { return true; }
