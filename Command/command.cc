#include "command.h"

void Cmd::unexecute(Model &editor) const {} // do nothing by default
bool Cmd::printsToScreen() const { return false;}
bool Cmd::changesState() const { return false; }
