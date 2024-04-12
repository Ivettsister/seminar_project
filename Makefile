CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJECTS = control.o game.o view.o main.o tview.o gview.o
TARGET = snake

all: ${TARGET}

${TARGET}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJECTS} ${LDFLAGS}

run:
	./${TARGET}

clean:
	${RM} ${OBJECTS} ${TARGET}

depend:
	${CXX} ${CXXFLAGS} ${OBJECTS:.o=.cpp} -MM >.depend

-include .depend
