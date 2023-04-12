#include "MVC/vim.h"
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        Vim editor {std::string()};
        editor.run();
    } else if (argc == 2) {
        Vim editor {argv[1]};
        editor.run();
    }
}
