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
	delete table_;
	/**for (int i=0; i<players_; i++) {
		delete players_[i];
	}**/
}

Deck* Game::getDeck() {
	return deck_;
}

Table* Game::getTable() {
	return table_;
}

bool Game::hasWinner() const {
	for (int i=0; i<4; i++) {
		if (players_[i]->getTotalScore()>=80) {
			return true;
		}
	}
	return false;
}

void Game::createPlayers() {
	string input;
	for (int i=0; i<4; ++i) {
		cout << "Is player " << i+1 << " a human(h) or a computer(c)?" << endl << ">";
		cin >> input;
		if (input == "h") {
			players_[i] = new HumanPlayer(i+1, 0, 0, this);
		}
		else {
			players_[i] =new ComputerPlayer(i+1, 0, 0, this);
		}
	}
}

void Game::declareWinner() {
	int min = players_[0]->getTotalScore();
	for (int i=0; i<4; i++) {
		if (players_[i]->getTotalScore()<min) {
			min=players_[i]->getTotalScore();
		}
	}
	for (int i=0; i<4; i++) {
		if (players_[i]->getTotalScore()==min) {
			cout<<"Player "<<players_[i]->getNumber()<<" wins!"<<endl;
		}
	}
}

void Game::notify(Card& card) {
	getTable()->addCard(card);
}

void Game::round() {
	int startPlayer;
	table_->clear();
	deck_->shuffle();

	for (int i=0; i<4; ++i) {
		Hand hand(*deck_, i+1);
		players_[i]->setHand(hand);
		players_[i]->clearListOfDiscards();
		if (players_[i]->has7S())
			startPlayer = i;
	}

	cout << "A new round begins. It's player " << startPlayer+1 << "'s turn to play." << endl;


	/* round begin */
	for (int i=0; i<52; ++i) {

		int curPlayer = (startPlayer+i)%4;

		vector<Card> legals = table_->getLegalCards();
		if (i != 0) {
			players_[curPlayer]->setLegalMoves(legals);
		} else {
			vector<Card> sevenS;
			sevenS.push_back(Card(SPADE, SEVEN));
			players_[curPlayer]->setLegalMoves(sevenS);
		}

		if (players_[curPlayer]->isHuman()) {
			cout << *table_;
			cout << *players_[curPlayer];

			Command c;

			bool isLegal = false;

			while (!isLegal) {
				cout << ">";
				cin>>c;
				if (c.type==PLAY) {

					if ( players_[curPlayer]->isLegalMoves(c.card)) {
						players_[curPlayer]->play(c.card);
						isLegal = true;
					} else {
						cout << "This is not a legal play." << endl;
					}

				} else if (c.type==DISCARD) {
					if ( !players_[curPlayer]->hasLegalMoves() ) {
						players_[curPlayer]->discard(c.card);
						isLegal = true;
					} else {
						cout << "You have a legal play. You may not discard." << endl;
					}
				} else if (c.type==DECK) {
					cout<<*deck_;
				} else if (c.type==QUIT) {
					delete this;
					exit(0);
				} else if (c.type==RAGEQUIT) {
					//RAGEQUIT
				} else if (c.type==BAD_COMMAND) {
					//BAD_COMMAND
				}
			}
			
		} else {
			Card dummy(SPADE,SEVEN);
			players_[curPlayer]->play(dummy); // the parameter is dummy
		}
	} /* round end */


	for (int i=0; i<4; ++i) {
		players_[i]->outputRoundEndResult();
		players_[i]->updateScore();
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
	while (!g->hasWinner()) {
		g->round();
	}
	g->declareWinner();
	return 0;
}