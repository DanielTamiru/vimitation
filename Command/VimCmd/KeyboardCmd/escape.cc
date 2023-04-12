#include "escape.h"
#include "../../../MVC/model.h"

void Escape::execute(Model &editor) const {
    editor.step(0, -1);
    editor.startCommandMode();
}
