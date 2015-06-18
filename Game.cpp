#include "Card.h"
#include "Game.h"
#include "Command.h"
#include "Deck.h"
#include "Table.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <vector>
#include <iostream>

using namespace std;

Game::Game(int seed) {
	deck_=new Deck(seed);
	table_=new Table();
	players_ = new Player*[4];
}

Game::~Game() {
	delete deck_;
}

Deck* Game::getDeck() {
	return deck_;
}

Table* Game::getTable() {
	return table_;
}

void Game::createPlayers() {
	string input;
	for (int i=0; i<4; ++i) {
		cout << "Is player " << i+1 << " a human(h) or a computer(c)?" << endl << ">";
		cin >> input;
		if (input == "h")
			players_[i] = new HumanPlayer(i+1, 0, this);
		else
			players_[i] =new ComputerPlayer(i+1, 0, this);
	}
}

void Game::notify(Card& card) {
	getTable()->addCard(card);
}

void Game::round() {
	int startPlayer;

	deck_->shuffle();

	for (int i=0; i<4; ++i) {
		Hand *hand = new Hand(*deck_, i+1);
		players_[i]->setHand(hand);
		if (players_[i]->has7S())
			startPlayer = i;
	}

	cout << "A new round begins. It's player " << startPlayer+1 << "'s turn to play." << endl;

	for (int i=0; i<52; ++i) {
		if (i != 0) {

		}
		int curPlayer = (startPlayer+i)%4;

		cout << "1" << endl;
		vector<Card> legals = table_->getLegalCards();
		cout << "2" << endl;
		for (int j=0; j<4; ++j)
			players_[j]->setLegalMoves(legals);

		if (players_[curPlayer]->isHuman()) {
			cout << *table_;
			cout << *players_[curPlayer];

			Command c;
			cout << ">";
			cin>>c;

			if (c.type==PLAY) {
				players_[curPlayer]->play(c.card);
				// cout<<c.card.getSuit()<<" "<<c.card.getRank()<<endl;
				// Card* card = new Card(c.card.getSuit(), c.card.getRank());
				// g->getTable()->addCard(*card);
				// cout<<*(g->getTable());

			} else if (c.type==DISCARD) {
				//DISCARD
			} else if (c.type==DECK) {
				cout<<*deck_;
			} else if (c.type==QUIT) {
				break;
			} else if (c.type==RAGEQUIT) {
				//RAGEQUIT
			} else if (c.type==BAD_COMMAND) {
				//BAD_COMMAND
			}
		} else {
			cout << players_[curPlayer]->getNumber() << endl;
		}
		
	}
}



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
	g->createPlayers();
	g->round();

	return 0;
}