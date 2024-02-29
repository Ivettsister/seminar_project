CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic
OBJECTS = control.o game.o view.o main.o
TARGET = snake

all: ${TARGET}

${TARGET}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJECTS} 

run:
	./${TARGET}

clean:
	${RM} ${OBJECTS} ${TARGET}
