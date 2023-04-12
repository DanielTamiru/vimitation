#ifndef COMMAND_H
#define COMMAND_H

class Model;

class Cmd {
    public:
        virtual void execute(Model &editor) const = 0;
        virtual void unexecute(Model &editor) const;

        virtual bool printsToScreen() const;
        virtual bool changesState() const;
};

#endif
