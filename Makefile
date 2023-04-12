CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
EXEC = vimitation
OBJECTS = main.o MVC/model.o MVC/vim.o MVC/view.o MVC/cursesview.o MVC/controller.o MVC/curseskeyboard.o \
	MVC/State/state.o MVC/State/vimstate.o MVC/Status/status.o MVC/Status/vimstatus.o \
	Command/command.o Command/VimCmd/vimcmd.o Command/VimCmd/KeyboardCmd/keyboardcmd.o Command/VimCmd/RegularCmd/regularcmd.o \
	Command/VimCmd/KeyboardCmd/character.o Command/VimCmd/KeyboardCmd/backspace.o Command/VimCmd/KeyboardCmd/newline.o Command/VimCmd/KeyboardCmd/escape.o \
	Command/VimCmd/RegularCmd/Movement/movement.o Command/VimCmd/RegularCmd/CtrlCmd/ctrlcmd.o Command/VimCmd/RegularCmd/Insertion/insertion.o Command/VimCmd/RegularCmd/ColonCmd/coloncmd.o Command/VimCmd/RegularCmd/Search/search.o \
	Command/VimCmd/RegularCmd/TextEdit/textedit.o Command/VimCmd/RegularCmd/TextEdit/Deletion/deletion.o Command/VimCmd/RegularCmd/TextEdit/Change/change.o \
	Ncurses/mycurses.o MVC/statusbar.o

DEPENDS = ${OBJECTS:.o=.d}


${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lncurses

-include ${DEPENDS}

.PHONY: clean
clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
