CXX= g++
CXXFLAGS = -std=c++0x -O -g `pkg-config gtkmm-2.4 --cflags`
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
OBJS =  models/Card.o models/Deck.o models/Hand.o models/Table.o models/Player.o models/HumanPlayer.o models/ComputerPlayer.o subject.o models/model_facade.o controller.o DeckGUI.o view.o main.o dialog.o
EXEC = mvc

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) $(LDFLAGS) -o $(EXEC)

clean:
	rm $(EXEC) $(OBJS)

DeckGUI.o: DeckGUI.h DeckGUI.cc
subject.o: subject.h subject.cc
# model.o: Card.h \
# 			Card.cpp \
# 			Deck.h \
# 			Deck.cpp \
# 			Hand.h \
# 			Hand.cpp \
# 			Table.h \
# 			Table.cpp \
# 			Player.h \
# 			Player.cpp \
# 			HumanPlayer.h \
# 			HumanPlayer.cpp \
# 			ComputerPlayer.h \
# 			ComputerPlayer.cpp \
# 			subject.h \
# 			model_facade.h \
# 			model_facade.cc
controller.o: controller.h models/model_facade.h controller.cc
view.o: view.h observer.h controller.h models/model_facade.h subject.h DeckGUI.h view.cc dialog.h dialog.cc
main.o: view.h controller.h models/model_facade.h main.cc
