CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g
OBJECTS = control.o game.o view.o main.o tview.o gview.o
TARGET = snake

all: ${TARGET}

${TARGET}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJECTS} 

run:
	./${TARGET}

clean:
	${RM} ${OBJECTS} ${TARGET}
