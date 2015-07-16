#ifndef _MODELFACADE_
#define _MODELFACADE_

#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Table.h"
#include "Player.h"
#include "../subject.h"
#include <vector>
#include <string>

class ModelFacade: public Subject {
private:
	std::vector<Player*> players_;
	std::vector<int> scores_;
	Deck* deck_;
	Table* table_;
	bool gameState_;
	int currentPlayer;
	int currentTurnInTheRound;

	void beginRound();
	void endRound();
	void clearPlayerScores();
	void computerMakeMove();
	void moveToNextPlayerAndTurn();
	void automateUntilNextHumanPlayer();
	void setLegalMovesForCurrentPlayer();
	bool hasWinner() const;
public:
	ModelFacade();

	/*Game logic*/
	void startGame(int); // start a game with seed
	void endGame(); // end the current game
	void setPlayerType(int, std::string);
	void selectCard(Card); // current user select a card
	void rageQuit();

	/*For views to update*/
	std::vector<Card> getTableCardsBySuit(Suit) const;
	std::vector<Card> getHand(int) const;
	std::vector<Card> getLegalPlays() const;
	bool getGameState() const;
	int getPoints(int) const;
	int getDiscards(int) const;
	int getCurrentPlayer() const;
	std::string getRoundEndResult() const;
	std::string getPlayedCardsString() const;
	void getWinners(std::vector<int>&) const; // pass in an empty int vector, return a vector of winner numbers
};


#endif