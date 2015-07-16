CXX= g++
CXXFLAGS = -std=c++0x -O -g `pkg-config gtkmm-2.4 --cflags`
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
OBJS =  subject.o \
		models/Card.o \
		models/Deck.o \
		models/Hand.o \
		models/Table.o \
		models/Player.o \
		models/HumanPlayer.o \
		models/ComputerPlayer.o \
		models/model_facade.o \
		controllers/controller.o \
		views/DeckGUI.o \
		views/dialog.o \
		views/view.o \
		main.o
EXEC = mvc

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) $(LDFLAGS) -o $(EXEC)

clean:
	rm $(EXEC) $(OBJS)

subject.o: subject.cc observer.h subject.h 