CXX= g++
CXXFLAGS = -std=c++0x -Wall -O -g `pkg-config gtkmm-2.4 --cflags`
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
OBJS = subject.o model.o controller.o DeckGUI.o view.o main.o dialog.o
EXEC = mvc

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) $(LDFLAGS) -o $(EXEC)

clean:
	rm $(EXEC) $(OBJS)

DeckGUI.o: DeckGUI.h DeckGUI.cc
model.o: subject.h ./models/model_facade.h ./models/model_facade.cc
subject.o: subject.h subject.cc
controller.o: controller.h ./models/model_facade.h controller.cc
view.o: view.h observer.h controller.h ./models/model_facade.h subject.h DeckGUI.h view.cc dialog.h dialog.cc
main.o: view.h controller.h ./models/model_facade.h main.cc
