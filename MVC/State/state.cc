#include "state.h"
#include <fstream>

State::State(): curX{0}, curY{0} {}
State::State(const std::string &file): filePath{file}, didChange{false}, curX{0}, curY{0} {
    std::fstream f {file};
    newFile = (f.fail())? true : false;
}
State::~State() {}
