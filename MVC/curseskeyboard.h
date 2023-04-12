#ifndef CURSESKEYBOARD_H
#define CURSESKEYBOARD_H

#include "controller.h"
#include "../Command/VimCmd/vimcmd.h"
#include "Status/vimstatus.h"
#include "../Ncurses/mycurses.h"
#include "statusbar.h"

#include "../Command/VimCmd/KeyboardCmd/keyboardcmd.h"
#include "../Command/VimCmd/RegularCmd/Movement/movement.h"
#include "../Command/VimCmd/RegularCmd/CtrlCmd/ctrlcmd.h"
#include "../Command/VimCmd/RegularCmd/Insertion/insertion.h"
#include "../Command/VimCmd/RegularCmd/ColonCmd/coloncmd.h"
#include "../Command/VimCmd/RegularCmd/Search/search.h"
#include "../Command/VimCmd/RegularCmd/TextEdit/Deletion/deletion.h"
#include "../Command/VimCmd/RegularCmd/TextEdit/Change/change.h"


#include <string>
#include <memory>
#include <map>


extern const Cmd* NO_COMMAND;
class InvalidCommand {};

class CursesKeyboard: public Controller {
    StatusBar &statusBar;
    Ncurses *ncurses;
    std::unique_ptr<VimStatus> currentStatus;
    std::string statusLabel;
    
    void fillMap();
    int getChar();

    std::map<int, std::unique_ptr<KeyboardCmd>> keyboardMap;
    
    // Map/Parser 1: Cursor Movement
    std::map<int, std::unique_ptr<Movement>> movementMap;
    Movement *parseMovement(int ch, int multiplier);
    // Map/Parer 2: Control Commands
    std::map<int, std::unique_ptr<CtrlCmd>> ctrlMap;
    CtrlCmd *parseCtrl(int ch, int multiplier);
    // Map/Parser 3: Insert Mode
    std::map<int, std::unique_ptr<Insertion>> insertMap;
    Insertion *parseInsert(int ch, int multiplier);
    // Map/Parser 4: Colon Commands
    std::map<std::string, std::unique_ptr<ColonCmd>> colonMap;
    ColonCmd *parseColon(int ch, int multiplier);
    // Map/Parser 5: TextEdit Commands
    std::map<int, std::unique_ptr<TextEdit>> editMap;
    std::map<int, std::unique_ptr<TextEdit>> specialEditMap;
    TextEdit *parseEdit(int ch, int multiplier);
    // Map/Parser 6: Search Commands
    std::map<int, std::unique_ptr<Search>> searchMap;
    Search *parseSearch(int ch, int multiplier);
    // Map/Parser 7: Repeat Commands
    std::map<int, RegularCmd*> repeatMap;
    RegularCmd *parseRepeat(int ch, int multiplier);

    int readCmdIn(int &multiplier);
    Cmd *parseCommand();
    Cmd *parseInput();

    
    void resetStatusLabel(); 

    public:
        CursesKeyboard(StatusBar &bar, Ncurses *ncurses); 
        ~CursesKeyboard(); 
        
        Cmd *readCommand() override;
        
        const std::string getStatusLabel() override;
        bool isON() override;
        bool isRecording() override;
        bool inInsertMode() override;
        bool inCommandMode() override;
        bool inReplaceMode() override;
        bool hasPrintableLabel() override;

        void turnOff() override;
        void setRecordingStatus(bool) override;
        void startInsertMode() override;
        void startCommandMode() override;
        void startReplaceMode() override;
        void setLabelPrintability(bool) override;
};


#endif
