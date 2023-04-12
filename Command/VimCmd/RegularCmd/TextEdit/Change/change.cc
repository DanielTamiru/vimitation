#include "change.h"

Change::~Change() {}

void ChangeMotion::executeOnce(Model &vim) const {
    int prevY = vim.y(), prevX = vim.x();
    motion->execute(vim);
    
    if (prevY != vim.y()) { // if Vertical motion
        int newY = vim.y();
        int y = (newY <= prevY)? newY: prevY;
        int yDiff = (newY <= prevY)? (prevY - newY): (newY - prevY);
        vim.move(y, 0);

        for (int i = 0; i < yDiff; ++i) {
            if (vim.y() >= 0) {
                vim.removeLine(vim.y());
                if (vim.y() < vim.lineCount()) vim.move(vim.y(), 0);   
                else vim.move(vim.y() - 1, 0);  
            }
        }
    } else { // else Horizontal
        std::string &line = vim.getLine(prevY);
        if (prevX <= vim.x()) line = line.erase(prevX, vim.x() - prevX);
        else line = line.erase(vim.x(), prevX - vim.x());
    }

    vim.startInsertMode();
}

void ChangeChars::executeOnce(Model &editor) const {
    if (editor.x() > 0) {
        editor.eraseChar(editor.y(), editor.x() + 1);
        if (editor.x() >= editor.lineLength(editor.y())) editor.step(0, -1);   
    } else if (editor.lineLength(editor.y()) == 1) editor.getLine(editor.y()).pop_back();

    editor.startInsertMode();

}

void ChangeLines::executeOnce(Model &editor) const {
    editor.getLine(editor.y()) = "";
    editor.move(editor.y(), 0);
    editor.startInsertMode();
}

ChangeHasCharField::~ChangeHasCharField() {}

void ReplaceWithChars::executeOnce(Model &vim) const {
    std::string &line = vim.getLine(vim.y());
    line[vim.x()] = c;

    vim.step(0, 1);
    vim.startInsertMode();
}

