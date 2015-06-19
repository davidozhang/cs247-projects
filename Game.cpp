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


/*
	Contructor: take an int as parameter
*/
Game::Game(int seed) {
	deck_=new Deck(seed);
	table_=new Table();
	players_ = new Player*[4];
}

/*
	Destructor
*/
Game::~Game() {
	delete deck_;
	delete table_;

	for (int i=0; i<4; i++)
		delete players_[i];
	delete[] players_;
}

/*
	Check if any player has accumulated score greater than or equal to 80
*/
bool Game::hasWinner() const {
	for (int i=0; i<4; i++)
		if (players_[i]->getTotalScore()>=80)
			return true;

	return false;
}

/*
	Initialize 4 players at the beginning of the game
	Prompt the user to enter if it is (h)uman or (c)omputer player
*/
void Game::createPlayers() {
	string input;
	for (int i=0; i<4; ++i) {
		cout << "Is player " << i+1 << " a human(h) or a computer(c)?" << endl << ">";
		cin >> input;

		if (input == "h")
			players_[i] = new HumanPlayer(i+1, 0, 0, this);
		else
			players_[i] =new ComputerPlayer(i+1, 0, 0, this);
	}
}

/*
	Output the winner(s)
*/
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

/*
	Add the card to the table
	Used by Player->play()
*/
void Game::notify(Card& card) {
	table_->addCard(card);
}

/*
	Main game logic for each round
*/
void Game::round() {
	int startPlayer;
	table_->clear();	// clear the table
	deck_->shuffle();	// shuffle the deck

	// for each player, set the hand based on the deck, clear the list of discarded cards
	for (int i=0; i<4; ++i) {
		Hand hand(*deck_, i+1);
		players_[i]->setHand(hand);
		players_[i]->clearListOfDiscards();
		if (players_[i]->has7S())
			startPlayer = i; // if the player has 7S, set the startPlayer to be this index
	}

	cout << "A new round begins. It's player " << startPlayer+1 << "'s turn to play." << endl;

	// the round begins
	for (int i=0; i<52; ++i) {

		int curPlayer = (startPlayer+i)%4; // get the index of the current player

		vector<Card> legals = table_->getLegalCards(); // get the list of legal cards from the table
		// set the list of legal cards; if it is the start player, 7S is the only legal move
		if (i != 0) {
			players_[curPlayer]->setLegalMoves(legals);
		} else {
			vector<Card> sevenS;
			sevenS.push_back(Card(SPADE, SEVEN));
			players_[curPlayer]->setLegalMoves(sevenS);
		}

		// if the player is human
		if (players_[curPlayer]->isHuman()) {
			cout << *table_;
			cout << *players_[curPlayer];

			Command c;

			bool isLegal = false;

			while (!isLegal) {
				cout << ">";
				cin>>c;
				if (c.type==PLAY) {
					// if the card is a legal move, play this card; else re-enter
					if ( players_[curPlayer]->isLegalMoves(c.card)) {
						players_[curPlayer]->play(c.card);
						isLegal = true;
					} else {
						cout << "This is not a legal play." << endl;
					}
				// if the player does not have legal play, discard this card; else re-enter
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
					cout<<"Player "<<players_[curPlayer]->getNumber()<<" ragequits. A computer will now take over."<<endl;
					// getting the parameters from the human player
					int score=players_[curPlayer]->getScore();
					int totalScore=players_[curPlayer]->getTotalScore();
					Hand hand=players_[curPlayer]->getHand();
					vector<Card> listOfDiscards = players_[curPlayer]->getListOfDiscards();
					delete players_[curPlayer];

					// setting the parameters for the new computer player
					players_[curPlayer] = new ComputerPlayer(curPlayer+1, score, totalScore, this);
					players_[curPlayer]->setHand(hand);					
					players_[curPlayer]->setListOfDiscards(listOfDiscards);
					if (i != 0) {
						players_[curPlayer]->setLegalMoves(legals);
					} else {
						vector<Card> sevenS;
						sevenS.push_back(Card(SPADE, SEVEN));
						players_[curPlayer]->setLegalMoves(sevenS);
					}

					// computer should play this round
					Card dummy(SPADE,SEVEN);
					players_[curPlayer]->play(dummy);
					isLegal = true;

				} else if (c.type==BAD_COMMAND) {
					//BAD_COMMAND
				}
			}
		// if the player is computer
		} else {
			Card dummy(SPADE,SEVEN);
			if (players_[curPlayer]->hasLegalMoves())
				players_[curPlayer]->play(dummy);
			else
				players_[curPlayer]->discard(dummy);
		}
	} // round end

	// output the result and update the score for all players at the end of each round
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
	delete g;
	return 0;
}