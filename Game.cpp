#include "Game.h"
#include "Command.h"
#include "Deck.h"
#include <set>
#include <iostream>

using namespace std;

Game::Game(int seed) {
	deck_=new Deck(seed);
}

Game::~Game() {
	delete deck_;
}

Deck* Game::getDeck() {
	return deck_;
}

int main(int argc, char* argv[]) {
	int seed;
	if (argc==2) {
		seed=atoi(argv[1]);
	} else {
		seed=0;
	}
	Game* g = new Game(seed);
	Command c;
	cin>>c;
	if (c.type==PLAY) {
		//PLAY
	} else if (c.type==DISCARD) {
		//DISCARD
	} else if (c.type==DECK) {
		cout<<*(g->getDeck());
	} else if (c.type==QUIT) {
		//QUIT
	} else if (c.type==RAGEQUIT) {
		//RAGEQUIT
	} else if (c.type==BAD_COMMAND) {
		//BAD_COMMAND
	}
	return 0;
}