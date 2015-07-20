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

	void beginRound();						// begin a round
	void endRound();						// end a round
	void clearPlayerScores();				// clear all players' scores
	void computerMakeMove();				// computer makes the move
	void moveToNextPlayerAndTurn();			// increment current player counter and turn counter
	void automateUntilNextHumanPlayer();	// IMPORTANT: advance to the next human player, game logic for winning the game and move to next round
	void setLegalMovesForCurrentPlayer();	// set the legal moves for the current player
	bool hasWinner() const;					// return true if there is at least a winner
public:
	ModelFacade();

	/*Game logic, called by controller*/
	void startGame(int); 					// start a game with seed
	void endGame(); 						// end the current game
	void setPlayerType(int, std::string);	// set the player type
	void selectCard(Card); 					// current user select a card
	void rageQuit();						// rage quit

	/*For views to update*/
	std::vector<Card> getTableCardsBySuit(Suit) const;	// get the cards on the table by suit
	std::vector<Card> getHand(int) const;				// get the hand of the player
	std::vector<Card> getLegalPlays() const;			// get the legal plays for the current player
	bool getGameState() const;							// get the current game state: true as "on" and false as "off"
	int getPoints(int) const;							// get the points by player number
	int getDiscards(int) const;							// get the number of discards by player number
	int getCurrentPlayer() const;						// get the current player number
	std::string getRoundEndResult() const;				// get the round end result string to display
	std::string getPlayedCardsString() const;			// get the played cards string to display
	void getWinners(std::vector<int>&) const; 			// get the winners by passing in an empty int vector, return a vector of winner numbers
};


#endif