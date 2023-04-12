#include "vim.h"
#include "cursesview.h"
#include "curseskeyboard.h"

#include <stdexcept>
#include <iostream>
#include <fstream>

Vim::Vim(const std::string &fileName): currentState{std::move(std::make_unique<VimState>(fileName))} {
    ncurses = std::move(std::make_unique<Ncurses>());
    addView(std::move(std::make_unique<CursesView>(*this, ncurses.get())));
    addController(std::move(std::make_unique<CursesKeyboard>(*this, ncurses.get())));
}

void Vim::run() {
    // Initial Display:
     try {
        if (!currentState->filePath.empty()) {
            read(currentState->filePath);
            
            if (std::fstream(currentState->filePath).peek() != std::ifstream::traits_type::eof()) // if file empty
                currentState->lines.erase(currentState->lines.begin());
            move(0,0);
            updateView();
        }
    } catch(FileDoesNotExist &err) {}
    displayView();
    printMsg(getFilePath());


    while (editing()) {
        // Get Command:
        try {
            const Cmd* command = getCommand();
            if (command) {
                command->execute(*this);
                if (command->changesState()) currentState->didChange = true;
                if (!command->printsToScreen()) {
                    updateView();
                    displayView();
                }
            }
        }
        // Error Display:
        catch (InvalidCommand err) { 
            std::cout << '\a';
            updateView();
            displayView();
        }
        catch (NoFileName err) { 
            updateView();
            displayView();
            printError("E32: No file name"); }
        catch (FileDoesNotExist err) { 
            updateView();
            displayView();
            printError("E484: Can't Open file"); } // add filename to message later
        catch (FileAlreadyExists err) { 
            updateView();
            displayView();
            printError("E13: File exists"); }
        catch (NoWriteSinceLastChange err) {   
            updateView();
            displayView();
            printError("E37: No write since last change"); 
        }
    }
}

void Vim::printMsg(std::string s) { view->printStatusBarMsg(s); }
void Vim::printError(std::string s) { view->printStatusBarErr(s); }


// GET METHODS

inline int Vim::y() { return currentState->curY; }

inline int Vim::x() { return currentState->curX; }

inline int Vim::windowWidth() { return view->windowWidth(); }

inline int Vim::windowHeight() { return view->windowHeight(); }

inline std::string &Vim::getLine(int i) { 
    if (i < 0 || i >= lineCount()) throw std::out_of_range("Line doesn't Exist");
    return currentState->lines[i]; 
}

inline int Vim::lineLength(int l) {
    if (l < 0 || l >= lineCount()) throw std::out_of_range("Line doesn't Exist");
    return currentState->lines[l].length(); 
}

inline int Vim::lineCount() { return currentState->lines.size(); }

// UTILITY METHODS

inline void Vim::move(int y, int x) { 
    if (y < 0) currentState->curY = 0;
    else if (y >= lineCount()) currentState->curY = lineCount() - 1;
    else currentState->curY = y;

    std::string &line = getLine(currentState->curY);
    int inCmdMode = typingCommands() && (line.length() > 0);

    if (x < 0) currentState->curX = 0;
    else if (x > line.length() - inCmdMode) currentState->curX = line.length() - inCmdMode;
    else currentState->curX = x;
}

inline void Vim::step(int y, int x) { this->move(currentState->curY + y, currentState->curX + x); }


void Vim::insertLine(int lineNum, const std::string &line) {
    if (lineNum < 0 || lineNum > lineCount()) throw std::out_of_range("Inserting line at invalid position");
    auto it = currentState->lines.begin();
    currentState->lines.insert(it + lineNum, line);
}

inline void Vim::appendLine(const std::string &line) { currentState->lines.push_back(line); }

void Vim::removeLine(int lineNum) {
    if (lineNum < 0 || lineNum >= lineCount()) throw std::out_of_range("Removing line that doesn't exist");
    auto it = currentState->lines.begin();
    currentState->lines.erase(it + lineNum);
}

inline void Vim::addChar(char c, int y, int x) {
    if (y < 0 || y >= lineCount()) throw std::out_of_range("Inserting char at line that doesn't exist");
    std::string &line = getLine(y);
    if (x < 0 || x > line.length()) throw std::out_of_range("Inserting char at invalid line position");
    line.insert(x, std::string(1, c)); 
}

inline void Vim::eraseChar(int y, int x) {
    if (y < 0 || y >= lineCount()) throw std::out_of_range("Erasing char at line that doesn't exist");
    std::string &line = getLine(y);
    if (x < 0 || x > line.length()) throw std::out_of_range("Erasing char at invalid line position");
    if (x > 0) line.erase(x - 1, 1);
    if (x == 0) line.erase(x, 1);
}

// *** FILE OPERATIONS ***

std::string Vim::getFilePath() { 
    std::string name = currentState->filePath;
    if (!name.empty()) name = "\"" + name + "\" ";

    // change the following to an isNew flag check
    if (currentState->newFile && name.find('/') != std::string::npos) name += "[NEW DIRECTORY]";
    else if (currentState->newFile) name += "[NEW FILE]";
    
    return name; 
}

inline void Vim::setFilePath(const std::string &fileName) { currentState->filePath = fileName; }

void Vim::write(const std::string &fileName) {
    // check if both current file and new file have no name
    if (currentState->filePath.empty() && fileName.empty()) throw NoFileName{}; // yup
    
    // check if new file already exists
    std::fstream fcheck {fileName};
    if (fileName != currentState->filePath && !fcheck.fail()) throw FileAlreadyExists{}; // yup
    
    // Create/grab the new file
    std::fstream f;
    if (fileName.empty()) f = std::fstream(currentState->filePath, std::fstream::trunc | std::fstream::in | std::fstream::out);
    else f = std::fstream(fileName, std::fstream::trunc | std::fstream::in | std::fstream::out);
    
    // Write to the file
    for (int lineNum = 0; lineNum < lineCount(); ++lineNum) {
        std::string line = getLine(lineNum);
        f << line << std::endl;
    }

    // Update new file status in state obj
    if (fileName.empty() || fileName == currentState->filePath) { // same file write
        currentState->newFile = false;
    } else { // new file write 
        currentState->newFile = true;
        currentState->filePath = fileName;
    }
    currentState->didChange = false;
    
}

void Vim::read(const std::string &file, int insertLine) {
    std::fstream f{file};
    if (f.fail()) throw FileDoesNotExist{};

    std::string fileLine;
    while (std::getline(f, fileLine)) {
        this->insertLine(++insertLine, fileLine);
    }
    step(1,0);
}

void Vim::quit() {
    if (currentState->didChange) throw NoWriteSinceLastChange{};
    control->turnOff();
}

void Vim::forceQuit() {
    control->turnOff();
}
