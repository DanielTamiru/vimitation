#include "deletion.h"

Delete::~Delete() {}

//-- d --//
void DelMotion::executeOnce(Model &vim) const {
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
}

//-- dd --//
void DelLines::executeOnce(Model &editor) const {
    if (editor.y() > 0) {
        editor.removeLine(editor.y());
        if (editor.y() < editor.lineCount()) editor.move(editor.y(), 0);   
        else editor.move(editor.y() - 1, 0);  
    } else if (editor.y() == 0) {
        editor.getLine(0) = "";
    }
}

//-- x --//
void  DelUnderAfter::executeOnce(Model &editor) const { // when x == 0
    if (editor.x() > 0) {
        editor.eraseChar(editor.y(), editor.x() + 1);
        if (editor.x() >= editor.lineLength(editor.y())) editor.step(0, -1);   
    } else if (editor.lineLength(editor.y()) == 1) editor.getLine(editor.y()).pop_back();
}

// -- X -- //
void  DelCharBefore::executeOnce(Model &editor) const {
    if (editor.x() > 0) {
        editor.eraseChar(editor.y(), editor.x());
        editor.step(0, -1);
    }
}

// -- J -- // remove line below (if it exists) and append it to current one following a space
void DelJoin::executeOnce(Model &vim) const {
    if (vim.y() < vim.lineCount() - 1) {
        std::string belowLine = vim.getLine(vim.y() + 1);
        vim.removeLine(vim.y() + 1);

        std::string &currentLine = vim.getLine(vim.y());
        int currentLineLen = vim.lineLength(vim.y());

        if (!belowLine.empty()) currentLine = currentLine.append(" ");
        currentLine = currentLine.append(belowLine);
        vim.move(vim.y(), currentLineLen + 1);
    }

}
