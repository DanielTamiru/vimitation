#include "controller.h"

const std::string Controller::getStatusLabel() { return ""; }

bool Controller::hasPrintableLabel() { return false; }
bool Controller::isON() { return true; }
bool Controller::isRecording() { return false; }
bool Controller::inInsertMode() { return false; }
bool Controller::inReplaceMode() { return false; }
bool Controller::inCommandMode() { return false; }

void Controller::setRecordingStatus(bool) {}
void Controller::startInsertMode() {}
void Controller::startCommandMode() {}
void Controller::startReplaceMode() {}
void Controller::setLabelPrintability(bool) {}
