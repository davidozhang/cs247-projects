#include "Game.h"
#include "Command.h"
#include "Deck.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
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

Game





// ****************************************************************
//		main
// ****************************************************************

int main(int argc, char* argv[]) {
	int seed;
	string input;

	if (argc==2) {
		seed=atoi(argv[1]);
	} else {
		seed=0;
	}
	Game* g = new Game(seed);

	for (int i=0; i<4; ++i) {
		cout << "Is player " << i+1 << " a human(h) or a computer(c)?" << endl << ">";
		cin >> input;
		g->newPlayer(i+1, input)
	}


	while (!g->hasWinner())
		g->startRound();

	cout << g->getWinners() << endl;



	// Command c;
	// cout<<">";
	// while (cin>>c) {
	// 	if (c.type==PLAY) {
	// 		//PLAY
	// 	} else if (c.type==DISCARD) {
	// 		//DISCARD
	// 	} else if (c.type==DECK) {
	// 		cout<<*(g->getDeck());
	// 	} else if (c.type==QUIT) {
	// 		break;
	// 	} else if (c.type==RAGEQUIT) {
	// 		//RAGEQUIT
	// 	} else if (c.type==BAD_COMMAND) {
	// 		//BAD_COMMAND
	// 	}
	// 	cout<<">";
	// }
	return 0;
}