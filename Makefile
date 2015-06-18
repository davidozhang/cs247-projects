CXX = g++
CXXFLAGS = -g -MMD -std=c++0x
OBJECTS = Card.o Command.o Deck.o Hand.o Table.o Player.o HumanPlayer.o ComputerPlayer.o Game.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
