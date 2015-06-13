CXX = g++
CXXFLAGS = -g -Wall -MMD -std=c++0x
OBJECTS = Card.o Command.o ComputerPlayer.o Deck.o Game.o Hand.o HumanPlayer.o Player.o Table.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
