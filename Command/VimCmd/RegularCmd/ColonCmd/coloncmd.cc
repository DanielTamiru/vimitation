#include "coloncmd.h"

ColonCmd::~ColonCmd() {}

void Write::executeOnce(Model &vim) const { vim.write(file); }

bool Read::changesState() const { return true; }
void Read::executeOnce(Model &vim) const { vim.read(file, vim.y()); }

void Quit::executeOnce(Model &vim) const { vim.quit(); }

void ForceQuit::executeOnce(Model &vim) const { vim.forceQuit(); }

void WriteQuit::executeOnce(Model &vim) const {
    vim.write(file);
    vim.forceQuit();
}

void toLineNumber::executeOnce(Model &vim) const {
    int lineNum = std::stoi(file);
    vim.move(lineNum - 1, 0);
}
