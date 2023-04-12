#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Status/status.h"
#include "../Command/command.h"
#include <string>

class Controller {
    public:
        virtual ~Controller() = default;
        
        virtual Cmd *readCommand() = 0;
        virtual const std::string getStatusLabel();
        

        virtual bool isON();
        virtual bool isRecording();
        virtual bool inInsertMode();
        virtual bool inCommandMode();
        virtual bool inReplaceMode();
        virtual bool hasPrintableLabel();
        //virtual bool inReplacementMode();
        

        virtual void turnOff() = 0;
        virtual void setRecordingStatus(bool recording);
        virtual void startInsertMode();
        virtual void startCommandMode();
        virtual void startReplaceMode();      
        virtual void setLabelPrintability(bool printability);
        //virtual void startReplacementMode();
};

#endif
