#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Table.h"
#include "Player.h"
#include "../subject.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include <vector>
#include <string>
using namespace std;


/* Constructor */
ModelFacade::ModelFacade() {
	deck_ = NULL;
	table_ = NULL;
	currentPlayer = -1;
	currentTurnInTheRound = 0;
	gameState_ = false;
	players_.resize(4);
	scores_.resize(4);
	for (int i=0; i<4; ++i) {
		players_[i] = NULL;
		scores_[i] = 0;
	}
}


/* 
* Private methods
*/

void ModelFacade::beginRound() {
	table_->clear();	// clear the table
	deck_->shuffle();	// shuffle the deck

	// for each player, set the hand based on the deck, clear the list of discarded cards
	for (int i=0; i<4; ++i) {
		Hand hand(*deck_, i+1);
		players_[i]->setHand(hand);
		players_[i]->clearListOfDiscards();
		if (players_[i]->has7S())
			currentPlayer = i; // if the player has 7S, set the startPlayer to be this index
	}

	state_ = "new round";
	notify();
	// cout << "A new round begins. It's player " << currentPlayer+1 << "'s turn to play." << endl;

	advancePlayer();
}

void ModelFacade::endRound() {
	for (int i=0; i<4; ++i) {
		scores_[i] += players_[i]->getRoundScore();
		players_[i]->clearListOfDiscards();
	}
}

void ModelFacade::clearPlayerScores() {
	for (int i=0; i<4; ++i)
		scores_[i] = 0;
}

void ModelFacade::computerMakeMove() {
	setLegalMovesForCurrentPlayer();
	Card dummy(SPADE,SEVEN);
	if (players_[currentPlayer]->hasLegalMoves())
		players_[currentPlayer]->play(dummy);
	else
		players_[currentPlayer]->discard(dummy);
}

void ModelFacade::setLegalMovesForCurrentPlayer() {
	vector<Card> legals = table_->getLegalCards(); // get the list of legal cards from the table
	// set the list of legal cards; if it is the start player, 7S is the only legal move
	if (currentTurnInTheRound != 0) {
		players_[currentPlayer]->setLegalMoves(legals);
	} else {
		vector<Card> sevenS;
		sevenS.push_back(Card(SPADE, SEVEN));
		players_[currentPlayer]->setLegalMoves(sevenS);
	}
}

bool ModelFacade::hasWinner() const {
	for (int i=0; i<4; i++)
		if (scores_[i] >= 80)
			return true;

	return false;
}

void ModelFacade::advancePlayer() {
	while (!players_[currentPlayer]->isHuman() && currentTurnInTheRound < 52) {
		computerMakeMove();
		currentPlayer = (currentPlayer+1)%4;
		currentTurnInTheRound++;
	}

	if (currentTurnInTheRound < 52)
		state_ = "new turn"; // update table
	else {
		state_ = "end round"; // output message
		// in update(), get the discards string and scores from model then display
	}
	notify();

	if (state_ == "end round") {
		endRound();
		if (!hasWinner())
			beginRound();
		else {
			state_ = "has winner";
			notify();
		}
	}
}

/* 
* Public methods
*/

void ModelFacade::startGame(int newseed) {
	// initialize deck
	if (NULL == deck_) {
		deck_ = new Deck(newseed);
	} else if (newseed != deck_->getSeed()) {
		deck_->setSeed(newseed);
	}

	// initialize table
	if (NULL == table_)
		table_ = new Table();
	else
		table_->clear();

	gameState_ = true;

	// initialize player scores
	clearPlayerScores();

	beginRound();
}

void ModelFacade::endGame() {
	table_->clear();
	clearPlayerScores();

	gameState_ = false;

	state_ = "end game";
	notify();
}

void ModelFacade::setPlayerType(int playerNumber, string playerType) {
	if (players_[playerNumber] != NULL)
		delete players_[playerNumber];

	if (playerType == "human")
		players_[playerNumber] = new HumanPlayer(playerNumber+1, this);
	else
		players_[playerNumber] = new ComputerPlayer(playerNumber+1, this);
}

void ModelFacade::selectCard(Card card) {
	setLegalMovesForCurrentPlayer();

	if (players_[currentPlayer]->hasLegalMoves() && !players_[currentPlayer]->isLegalMoves(card)) {
		state_ = "invalid play";
		notify();
		return;
	} else if (players_[currentPlayer]->isLegalMoves(card)) {
		players_[currentPlayer]->play(card);
	} else {
		players_[currentPlayer]->discard(card);
	}

	currentPlayer = (currentPlayer+1)%4;
	currentTurnInTheRound++;

	advancePlayer();
}

void ModelFacade::rageQuit() {
	Hand hand=players_[currentPlayer]->getHand();
	vector<Card> listOfDiscards = players_[currentPlayer]->getListOfDiscards();
	delete players_[currentPlayer];

	// setting the parameters for the new computer player
	players_[currentPlayer] = new ComputerPlayer(currentPlayer+1, this);
	players_[currentPlayer]->setHand(hand);					
	players_[currentPlayer]->setListOfDiscards(listOfDiscards);

	advancePlayer();
}

void ModelFacade::addCardToTable(Card card) {
	table_->addCard(card);
}


string ModelFacade::getRoundEndResult() const {
	string result = "";

	for (int i=0; i<4; ++i) {
		int score = players_[i]->getRoundScore();
		result += players_[i]->getListOfDiscardsString();

		result += ("Player " + to_string(i+1) + "'s score: "); 
		result += (to_string(scores_[i]) + " + " +
					to_string(score) + " = " +
					to_string(scores_[i] + score) + "\n");
	}
	return result;
}

vector<Card> ModelFacade::getHand(int playerNumber) const {
	return players_[playerNumber]->getHand().getCards();
}

vector<Card> ModelFacade::getTableCardsBySuit(Suit suit) const {
	return table_->getTableCardsBySuit(suit);
}

int ModelFacade::getPoints(int playerNumber) const {
	return scores_[playerNumber];
}

int ModelFacade::getDiscards(int playerNumber) const {
	return players_[playerNumber]->getListOfDiscards().size();
}

int ModelFacade::getCurrentPlayer() const {
	return currentPlayer;
}

bool ModelFacade::getGameState() const {
	return gameState_;
}

void ModelFacade::getWinners(vector<int>& winners) const {
	int min = scores_[0];
	for (int i=1; i<4; i++) {
		if (scores_[i]<min) {
			min=scores_[i];
		}
	}
	for (int i=0; i<4; i++) {
		if (scores_[i]==min) {
			winners.push_back(i);
		}
	}
}
