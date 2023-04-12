#include "search.h"
#include "algorithm"

Search::~Search() {}

/**- ? -**/
void SearchLeft::executeOnce(Model &vim) const {
    int y = vim.y(), x = vim.x();

    std::string reverse_word = word;
    std::reverse(reverse_word.begin(), reverse_word.end());

    // check current line
    std::string firstLine = (vim.getLine(y)).substr(0, x);
    std::reverse(firstLine.begin(), firstLine.end());

    int posn = firstLine.find(reverse_word);
    if (posn != std::string::npos) {
        vim.move(y, firstLine.length() - posn - word.length());
        return;
    }

    // check rest of file
    for (int lineNum = y - 1; lineNum >= 0; --lineNum) {
        std::string line = vim.getLine(lineNum);
        std::reverse(line.begin(), line.end());

        int posn = line.find(reverse_word);
        if (posn !=  std::string::npos) {
            vim.move(lineNum, line.length() - posn - word.length());
            return;
        }
    }
}

/**- / -**/
void SearchRight::executeOnce(Model &vim) const {
    int y = vim.y(), x = vim.x();
    // check current line
    std::string firstLine = vim.getLine(y);
    if (x < firstLine.length() - 1 && firstLine.length() > 0) {
        int firstLinePosn = (firstLine.substr(x + 1)).find(word);
        if (firstLinePosn != std::string::npos) {
            vim.move(y, x + 1 + firstLinePosn);
            return;
        }
    }
    // check rest of file
    int count = vim.lineCount();
    for (int lineNum = y + 1; lineNum < count; ++lineNum) {
        if (vim.lineLength(lineNum) > 0) {
             int posn = vim.getLine(lineNum).find(word);
            if (posn !=  std::string::npos) {
                vim.move(lineNum, posn);
                return;
            }
        }
    }
}