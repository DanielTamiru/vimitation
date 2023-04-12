#ifndef VIMSTATUS_H
#define VIMSTATUS_H

#include "status.h"
enum Mode {COMMAND, INSERTION, REPLACEMENT};

class VimStatus: public Status {
    public:
        Mode mode;
        bool isRecording; 
        bool hasPrintableLabel;
        VimStatus();
};

#endif
