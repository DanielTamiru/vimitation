#ifndef MODEL_H
#define MODEL_H

#include "controller.h"
#include "view.h"

#include <memory>
#include <vector>


class Model {
    protected:
        std::unique_ptr<View> view; // **
        std::unique_ptr<Controller> control; // **
    
        void addView(std::unique_ptr<View>); // **
        void addController(std::unique_ptr<Controller>); // **
        
        const Cmd *getCommand(); // **
        void updateView(); // **
        void displayView(); // **
    public:
        virtual ~Model() = 0;
        
        bool editing(); // **
        bool typingCommands(); // might not need
        bool insertingText(); // might not need
        bool replacingText(); // might not need
        bool recording();
        bool hasPrintableLabel(); // might not need
        void setRecordingStatus(bool);
        void startInsertMode();
        void startCommandMode();
        void startReplaceMode();
        
        // State Get methods
        virtual int y() = 0;
        virtual int x() = 0;
        virtual int windowWidth() = 0;
        virtual int windowHeight() = 0;
        virtual std::string &getLine(int l) = 0; // **
        virtual int lineLength(int l) = 0; 
        virtual int lineCount() = 0; // **
        

        // State Change & Set methods
        virtual void move(int y, int x) = 0; // **
        virtual void step(int y, int x) = 0; // **
        virtual void insertLine(int lineNum, const std::string &line) = 0; // **
        virtual void appendLine(const std::string &line) = 0;
        virtual void removeLine(int lineNum) = 0; // **
        virtual void addChar(char c, int y, int x) = 0;  // **
        virtual void eraseChar(int y, int x) = 0; // **

        // File Methods
        virtual std::string getFilePath() = 0;
        virtual void setFilePath(const std::string &file) = 0; 
        virtual void write(const std::string &file = std::string()) = 0; // **
        virtual void read(const std::string &file, int line = 0) = 0; // **
        virtual void quit() = 0; // **
        virtual void forceQuit() = 0; // **
        
};

#endif
