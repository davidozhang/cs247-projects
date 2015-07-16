#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Table.h"
#include "Player.h"
#include "../subject.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "model_facade.h"
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
	currentTurnInTheRound = 0;
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
	cout << "A new round begins. It's player " << currentPlayer+1 << "'s turn to play." << endl;

	automateUntilNextHumanPlayer();
}

void ModelFacade::endRound() {
	for (int i=0; i<4; ++i) {
		players_[i]->outputRoundDiscards();
		int score = players_[i]->getRoundScore();

		cout << "Player " << i+1 << "'s score: "; 
		cout << scores_[i] << " + " << score << " = " << scores_[i] + score << endl;

		scores_[i] += score;
		players_[i]->clearListOfDiscards();
	}
}

void ModelFacade::clearPlayerScores() {
	for (int i=0; i<4; ++i)
		scores_[i] = 0;
}

void ModelFacade::computerMakeMove() {
	setLegalMovesForCurrentPlayer();
	Card empty(NOSUIT,NORANK);
	if (players_[currentPlayer]->hasLegalMoves())
		players_[currentPlayer]->play(empty);
	else
		players_[currentPlayer]->discard(empty);
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

void ModelFacade::moveToNextPlayerAndTurn() {
	currentPlayer = (currentPlayer+1)%4;
	currentTurnInTheRound++;
}

void ModelFacade::automateUntilNextHumanPlayer() {
	while (!players_[currentPlayer]->isHuman() && currentTurnInTheRound < 52) {
		computerMakeMove();
		moveToNextPlayerAndTurn();
	}

	if (currentTurnInTheRound < 52) {
		state_ = "new turn";
		setLegalMovesForCurrentPlayer();
		cout << *table_;
		cout << *players_[currentPlayer];
	} else {
		state_ = "end round";
	}
	notify();

	if (state_ == "end round") {
		endRound();
		if (!hasWinner())
			beginRound();
		else {
			state_ = "has winner";
			vector<int> winners;
			getWinners(winners);
			for (int i=0; i<winners.size(); ++i)
				cout << "Player " <<winners[i]+1<<" wins!" << endl;
			notify();
			gameState_ = false;
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

	for (int i=0; i<4; ++i)
		players_[i]->setTable(table_);

	gameState_ = true;

	// initialize player scores
	clearPlayerScores();

	beginRound();
}

void ModelFacade::endGame() {
	if (NULL != table_)
		table_->clear();
	
	clearPlayerScores();

	gameState_ = false;

	state_ = "end game";
	notify();
}

void ModelFacade::setPlayerType(int playerNumber, string playerType) {
	if (players_[playerNumber] != NULL)
		delete players_[playerNumber]; 

	if (playerType == "h")
		players_[playerNumber] = new HumanPlayer(playerNumber+1, table_);
	else
		players_[playerNumber] = new ComputerPlayer(playerNumber+1, table_);
}

void ModelFacade::selectCard(Card card) {
	if (players_[currentPlayer]->hasLegalMoves() && !players_[currentPlayer]->isLegalMoves(card)) {
		cout << card << " This play is illegal." << endl;
		state_ = "invalid play";
		notify();
		return;
	} else if (players_[currentPlayer]->isLegalMoves(card)) {
		players_[currentPlayer]->play(card);
	} else { // if legal move is empty
		players_[currentPlayer]->discard(card);
	}

	moveToNextPlayerAndTurn();
	automateUntilNextHumanPlayer();
}

void ModelFacade::rageQuit() {
	cout<<"Player "<< currentPlayer+1 <<" ragequits. A computer will now take over."<<endl;

	Hand hand=players_[currentPlayer]->getHand();
	vector<Card> listOfDiscards = players_[currentPlayer]->getListOfDiscards();
	delete players_[currentPlayer];

	// setting the parameters for the new computer player
	players_[currentPlayer] = new ComputerPlayer(currentPlayer+1, table_);
	players_[currentPlayer]->setHand(hand);					
	players_[currentPlayer]->setListOfDiscards(listOfDiscards);

	automateUntilNextHumanPlayer();
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
	vector<Card> hand = players_[playerNumber]->getHand().getCards();
	int size = 13 - hand.size();
	while (size-- > 0)
		hand.push_back(Card(NOSUIT, NORANK));

	return hand;
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
