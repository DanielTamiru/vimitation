#ifndef VIM_H
#define VIM_H

#include "model.h"
#include "State/vimstate.h"
#include "../Ncurses/mycurses.h"
#include "statusbar.h"

#include <memory>
#include <vector>
#include <string>


class NoFileName {};
class FileDoesNotExist {};
class FileAlreadyExists {};
class NoWriteSinceLastChange{};

class Vim: public Model, public StatusBar {
    
    public:
        std::unique_ptr<Ncurses> ncurses; // try making these priveate
        std::unique_ptr<VimState> currentState; 
        
        Vim(const std::string &fileName);
        void run();
        void printError(std::string s) override;
        void printMsg(std::string s) override;
        
        // State Get methods
        int y() override;
        int x() override;
        int windowWidth() override;
        int windowHeight() override;
        std::string &getLine(int l) override;
        int lineLength(int l) override;
        int lineCount() override;
        
        // State Change & Set methods
        void move(int y, int x) override;
        void step(int y, int x) override;
        void insertLine(int lineNum, const std::string &line) override;
        void appendLine(const std::string &line) override;
        void removeLine(int lineNum) override;
        void addChar(char c, int y, int x) override;
        void eraseChar(int y, int x) override;
        
        //file methods
        std::string getFilePath() override;
        void setFilePath(const std::string &file) override;
        virtual void write(const std::string &file = std::string()) override;
        virtual void read(const std::string &file, int insertLine = 0) override;
        virtual void quit() override;
        virtual void forceQuit() override;
    
    struct StateArchive {
        std::vector<std::unique_ptr<VimState>> prevStates;
    };
    StateArchive pastStates;
    /** Fields to be added **/
};

#endif
