CXX = g++
CXXFLAGS = -g -MMD -std=c++0x
OBJECTS = 	models/Card.o \
			models/Command.o \
			models/Deck.o \
			models/Hand.o \
			models/Table.o \
			models/Player.o \
			models/HumanPlayer.o \
			models/ComputerPlayer.o \
			models/Game.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
