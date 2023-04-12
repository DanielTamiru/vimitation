#include "curseskeyboard.h"
#include "Status/vimstatus.h"

#include <stdexcept>
#include <set>
#include <sstream>

// Insert Mode "Commands"
#include "../Command/VimCmd/KeyboardCmd/character.h"
#include "../Command/VimCmd/KeyboardCmd/backspace.h"
#include "../Command/VimCmd/KeyboardCmd/newline.h"
#include "../Command/VimCmd/KeyboardCmd/escape.h"

const Cmd* NO_COMMAND = nullptr;

const static int CHARACTER = -1;
const static int ESCAPE = 27;
const static int NEWLINE = 10;

const static int TOPREVPAGE = -11;
const static int TONEXTPAGE = -22;
const static int TOPREVwLINE = -33;
const static int TONEXTwLINE = -44;

bool isWhileSpace(char c) { return c == ' ' || c == '\t';}
bool isDigit(char c) { return '0' <= c && c <= '9';}

CursesKeyboard::CursesKeyboard(StatusBar &bar, Ncurses *ncurses): 
        currentStatus{std::move(std::make_unique<VimStatus>())}, 
        ncurses{ncurses}, statusBar{bar} {
    fillMap();
} 
CursesKeyboard::~CursesKeyboard() { endwin(); }

int CursesKeyboard::getChar() {
    int ch = ncurses->getCharacter();
    
    if ((ch == ':' || ch == '/' || ch == '?') && statusLabel == "") setLabelPrintability(true);
    if (ch != '\n' && ch != ncurses->BACKSPACE_KEY && ch != 127) statusLabel += (char)ch;
    else if ((ch == ncurses->BACKSPACE_KEY || ch == 127) && !statusLabel.empty()) statusLabel.pop_back();
    if (hasPrintableLabel()) statusBar.printMsg(statusLabel);
    return ch;
}

void CursesKeyboard::fillMap() {
    // Fill Keyboard Cmd Map
    keyboardMap[CHARACTER] = std::move(std::make_unique<Character>(' '));
    keyboardMap[KEY_BACKSPACE] = std::move(std::make_unique<Backspace>());
    keyboardMap[127] = std::move(std::make_unique<Backspace>());
    keyboardMap[10] = std::move(std::make_unique<Newline>());
    keyboardMap[27] = std::move(std::make_unique<Escape>());

    // Fill Movement Cmd Map
    movementMap[48] = std::move(std::make_unique<ToFirstChar>());
    movementMap[36] = std::move(std::make_unique<ToLastChar>());
    movementMap[104] = std::move(std::make_unique<ToLeft>());
    movementMap[108] = std::move(std::make_unique<ToRight>());
    movementMap[107] = std::move(std::make_unique<ToPrevLine>());
    movementMap[106] = std::move(std::make_unique<ToNextLine>());
    movementMap[98] = std::move(std::make_unique<ToPrevWord>());
    movementMap[119] = std::move(std::make_unique<ToNextWord>());
    movementMap[94] = std::move(std::make_unique<ToFirstNonBlankChar>());
    movementMap[70] = std::move(std::make_unique<ToPrevChar>());
    movementMap[102] = std::move(std::make_unique<ToNextChar>());

    // Fill Ctrl Cmd Map
    ctrlMap['B'] = std::move(std::make_unique<ToPrevPage>());
    ctrlMap['F'] = std::move(std::make_unique<ToNextPage>());
    ctrlMap['U'] = std::move(std::make_unique<ToPrevWLine>());
    ctrlMap['D'] = std::move(std::make_unique<ToNextWLine>());
    ctrlMap['G'] = std::move(std::make_unique<ShowFileName>());

    // Fill Insert Cmd Map
    insertMap['i'] = std::move(std::make_unique<InsertLeft>());
    insertMap['a'] = std::move(std::make_unique<InsertRight>());
    insertMap['I'] = std::move(std::make_unique<InsertLineStart>());
    insertMap['A'] = std::move(std::make_unique<InsertLineEnd>());
    insertMap['o'] = std::move(std::make_unique<InsertLineBelow>());
    insertMap['O'] = std::move(std::make_unique<InsertLineAbove>());
    insertMap['R'] = std::move(std::make_unique<Replace>());

    // Fill Colon Cmd Map
    colonMap["w"] = std::move(std::make_unique<Write>());
    colonMap["q"] = std::move(std::make_unique<Quit>());
    colonMap["wq"] = std::move(std::make_unique<WriteQuit>());
    colonMap["q!"] = std::move(std::make_unique<ForceQuit>());
    colonMap["r"] = std::move(std::make_unique<Read>());
    colonMap["line-number"] = std::move(std::make_unique<toLineNumber>());

    // Fill TextEdit Map
    specialEditMap['d'] = std::move(std::make_unique<DelMotion>());
    specialEditMap['c'] = std::move(std::make_unique<ChangeMotion>());
    editMap['d'] = std::move(std::make_unique<DelLines>());
    editMap['x'] = std::move(std::make_unique<DelUnderAfter>());
    editMap['X'] = std::move(std::make_unique<DelCharBefore>());
    editMap['J'] = std::move(std::make_unique<DelJoin>());
    editMap['c'] = std::move(std::make_unique<ChangeLines>());
    editMap['r'] = std::move(std::make_unique<ReplaceWithChars>());
    editMap['s'] = std::move(std::make_unique<ChangeChars>());
    editMap['S'] = std::move(std::make_unique<ChangeLines>());

    // Fill Search Map
    searchMap['?'] = std::move(std::make_unique<SearchLeft>());
    searchMap['/'] = std::move(std::make_unique<SearchRight>());

    // Fill Repeat Map
    repeatMap['.'] = nullptr; // last edit
    repeatMap[';'] = nullptr; // last char move
    repeatMap['n'] = nullptr; // last search
    repeatMap['N'] = nullptr; // opposite direction
}

int CursesKeyboard::readCmdIn(int &mult) {
    int ch = getChar();
    if (ch != 48) { // if not zero command
        for (int p = 0; 48 <= ch && ch <= 57; ++p) {
            int dig = ch - 48; // convert ascii digit to integers

            mult = 10 * mult + dig;
            ch = getChar();
        }
    }
    if (mult == 0) mult = 1;

    return ch;
}

Insertion *CursesKeyboard::parseInsert(int ch, int multiplier) {
    Insertion *cmd = insertMap.at(ch).get();
    cmd->multiplier = multiplier;
    return cmd;
}

Movement *CursesKeyboard::parseMovement(int ch, int multiplier) {
    Movement *cmd = movementMap.at(ch).get();
    cmd->multiplier = multiplier;
    
    if (HasCharField *charCmd = dynamic_cast<HasCharField*>(cmd)) {
        charCmd->c = (char)(getChar());
        repeatMap[';'] = charCmd;
        return charCmd;
    }
    return cmd;
}


CtrlCmd *CursesKeyboard::parseCtrl(int ch, int multiplier)  {
    std::string ctrlString = unctrl(ch);

    if (ctrlString.length() == 2) {
        CtrlCmd *cmd = ctrlMap.at(ctrlString[1]).get();
        cmd->multiplier = multiplier;
        if (HasStatusBar *printCmd = dynamic_cast<HasStatusBar*>(cmd)) {
            printCmd->bar = &statusBar;
            return printCmd;
        }
        return cmd;
    } 
    else throw std::out_of_range ("Not a Ctrl Command");
    return nullptr;
}



ColonCmd *CursesKeyboard::parseColon(int ch, int multiplier)  {
    if (ch == ':') {
        std::stringstream cmdInput;
        int charCount = 1;

        ch = getChar();
        while (ch != '\n') {
            if (ch != ncurses->BACKSPACE_KEY && ch != 127) {
                ++charCount;
                cmdInput << (char)ch;
            }
            else --charCount; 
            if (charCount == 0) throw std::out_of_range ("Backed out of colon command");

            ch = getChar(); 
        }

        std::string cmdName;
        cmdInput >> cmdName;

        ColonCmd *cmd;
        if (isDigit(cmdName[0])) {
            cmd = colonMap.at("line-number").get();
            cmd->file = cmdName;
        } else {
            cmd = colonMap.at(cmdName).get();
            cmd->file = "";
            try { cmdInput >> cmd->file;}
            catch (...) {}
        }

        cmd->multiplier = multiplier;
        return cmd;
    }
    else throw std::out_of_range ("Not a Colon Command");
    return nullptr;
}


Search *CursesKeyboard::parseSearch(int ch, int multiplier)  {
    if (ch == '/' || ch == '?') {
        std::string pattern = std::string(1, (char)ch);

        int c = getChar();
        while (c != '\n') {
            if (pattern.empty()) throw std::out_of_range ("Backed out of colon command");
            else if (c == ncurses->BACKSPACE_KEY || c == 127) pattern.pop_back();
            else pattern += (char)c;

            c = getChar(); 
        } 
        pattern = pattern.substr(1);
        
        Search *cmd = searchMap.at(ch).get();
        cmd->multiplier = multiplier;   
        cmd->word = pattern;
        
        repeatMap['n'] = cmd;
        Search *oppCmd;
        if (ch == '/') oppCmd = searchMap['?'].get();
        else oppCmd = searchMap['/'].get();
        oppCmd->multiplier = multiplier;   
        oppCmd->word = pattern;
        repeatMap['N'] = oppCmd;
        
        return cmd;
    }
    else throw std::out_of_range ("Not a Colon Command");
    return nullptr;
}

TextEdit *CursesKeyboard::parseEdit(int ch, int multiplier) {
    std::set<char> doubleCmds = {'d', 'c'}; // these can be passed motions, or be doubled (eg dd)
    
    if (doubleCmds.find(ch) != doubleCmds.end()) {
        int incompMoveMultiplier = 1;
        int incompMoveCmd = readCmdIn(incompMoveMultiplier);
        
        if (doubleCmds.find(incompMoveCmd) != doubleCmds.end()) {
            TextEdit *cmd = editMap.at(ch).get();
            cmd->multiplier = multiplier;
            repeatMap['.'] = cmd;
            return cmd;
        }
        
        Movement *move = parseMovement(incompMoveCmd, incompMoveMultiplier);
        TextEdit *cmd = specialEditMap.at(ch).get();
        cmd->multiplier = multiplier;
        cmd->motion = move;
        repeatMap['.'] = cmd;
        return cmd;
    }

    TextEdit *cmd = editMap.at(ch).get();
    cmd->multiplier = multiplier;
    if (ChangeHasCharField *charCmd = dynamic_cast<ChangeHasCharField*>(cmd)) {
        charCmd->c = (char)(getChar());
        repeatMap['.'] = charCmd;
        return charCmd;
    }
    repeatMap['.'] = cmd;
    return cmd;
}

RegularCmd *CursesKeyboard::parseRepeat(int ch, int multiplier) {
    RegularCmd *cmd = repeatMap.at(ch);
    if (cmd == nullptr) throw std::out_of_range ("Command cannot be repeated because it has not been used");
    cmd->multiplier = multiplier;
    return cmd;
}

Cmd *CursesKeyboard::parseCommand() {
    int multiplier = 0;
    int ch = readCmdIn(multiplier);

    try {
        return parseCtrl(ch, multiplier);
    } catch (const std::out_of_range& error) {}
    try {
        return parseMovement(ch, multiplier);
    } catch (const std::out_of_range& error) {}
    try {
        return parseInsert(ch, multiplier);
    } catch (const std::out_of_range& error) {}
    try {
        return parseColon(ch, multiplier);
    } catch (const std::out_of_range& error) {}
    try {
        return parseEdit(ch, multiplier);
    } catch (const std::out_of_range& error) {}
    try {
        return parseSearch(ch, multiplier);
    } catch (const std::out_of_range& error) {}
    try {
        return parseRepeat(ch, multiplier);
    } catch (const std::out_of_range& error) {}

    throw InvalidCommand{};
    return nullptr;
}

Cmd *CursesKeyboard::parseInput() {
    int ch = getChar();

    if (ch == NEWLINE || ch == ESCAPE || ch == ncurses->BACKSPACE_KEY || ch == 127) {
        KeyboardCmd *cmd = keyboardMap[ch].get();
        return cmd;
    }
    else { // Read as Character
        KeyboardCmd *cmd = keyboardMap[CHARACTER].get();
        Character *theChar = static_cast<Character*>(cmd);
        theChar->c = (char)ch;
        return theChar;
    }
}

Cmd *CursesKeyboard::readCommand() {
    resetStatusLabel();
    setLabelPrintability(false);

    if (inCommandMode()) return parseCommand();
    else return parseInput();
}

const std::string CursesKeyboard::getStatusLabel() { 
    if (hasPrintableLabel()) return statusLabel; 
    else return "";
}
    
void CursesKeyboard::resetStatusLabel() { statusLabel = ""; }

inline bool CursesKeyboard::isON() { return currentStatus->isON; }
inline bool CursesKeyboard::isRecording() { return currentStatus->isRecording; }
inline bool CursesKeyboard::inInsertMode() { return currentStatus->mode == INSERTION; }
inline bool CursesKeyboard::inCommandMode() { return currentStatus->mode == COMMAND; }
inline bool CursesKeyboard::inReplaceMode() { return currentStatus->mode == REPLACEMENT; }
inline bool CursesKeyboard::hasPrintableLabel() { return currentStatus->hasPrintableLabel; }

inline void CursesKeyboard::turnOff() { currentStatus->isON = false; }
inline void CursesKeyboard::setRecordingStatus(bool recordingStatus) {currentStatus->isRecording = recordingStatus; }
inline void CursesKeyboard::startInsertMode() { currentStatus->mode = INSERTION; }
inline void CursesKeyboard::startCommandMode() { currentStatus->mode = COMMAND; }
inline void CursesKeyboard::startReplaceMode() { currentStatus->mode = REPLACEMENT; }
inline void CursesKeyboard::setLabelPrintability(bool printability) { currentStatus->hasPrintableLabel = printability; }
