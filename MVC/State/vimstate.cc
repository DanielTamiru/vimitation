#include "vimstate.h"

VimState::VimState(const std::string &file): State(file), lines{std::string("")} {}
