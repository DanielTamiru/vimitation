#include "regularcmd.h"

RegularCmd::RegularCmd(): multiplier{1} {}

void RegularCmd::preExecute(Model &editor) const {} // do nothing by default

void RegularCmd::execute(Model &editor) const {
    preExecute(editor);
    for(int exec = 0; exec < multiplier; exec++) executeOnce(editor);
    postExecute(editor);
}

void RegularCmd::postExecute(Model &editor) const {} // do nothing by default
