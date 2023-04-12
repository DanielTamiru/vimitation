#include "model.h"
#include <utility>

// Model::Model(std::unique_ptr<State> state): currentState{std::move(state)} {}
Model::~Model() {}

void Model::addView(std::unique_ptr<View> v) { view = std::move(v); }

void Model::addController(std::unique_ptr<Controller> c) { control = std::move(c); }

const Cmd *Model::getCommand() { return control->readCommand(); }

void Model::updateView() { view->update(); }
void Model::displayView() { view->displayView(); }

bool Model::editing() { return control->isON(); }
bool Model::typingCommands() { return control->inCommandMode(); }
bool Model::insertingText() { return control->inInsertMode(); }
bool Model::replacingText() { return control->inReplaceMode(); }
bool Model::recording() { return control->isRecording(); }
bool Model::hasPrintableLabel() { return control->hasPrintableLabel(); }
void Model::setRecordingStatus(bool isRecording) { control->setRecordingStatus(isRecording); }
void Model::startInsertMode() { control->startInsertMode(); }
void Model::startCommandMode() { control->startCommandMode(); }
void Model::startReplaceMode() { control->startReplaceMode(); }