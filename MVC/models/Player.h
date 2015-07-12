#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <iostream>
#include "Game.h"
#include "Hand.h"
#include "Card.h"


class Game;

class Player {
	friend std::ostream &operator<<(std::ostream &, const Player &);

public:

	// do validation before the play
	// card has to be in legalMoves
	// essentially, call isLegalMoves(card)
	virtual void play(Card&) =0;

	// do validation before the discard
	// assume there is no legal play
	// essentially, call hasLegalMoves()
	virtual void discard(Card&) =0;

	virtual ~Player();

	void setHand(Hand&);								// setter for hand
	void setLegalMoves(const std::vector<Card>&);		// setter for updating the set of legal moves
	void setListOfDiscards(const std::vector<Card>&); 	// setter for the list of discards

	Hand getHand() const;								// getter for hand
	int getTotalScore() const;							// getter for total score
	int getScore() const;								// getter for (round) score
	int getNumber() const;								// getter for player number
	std::vector<Card> getListOfDiscards() const;		// getter for list of discards card

	void clearListOfDiscards(); 						// clear the list of discards
	void outputRoundEndResult() const;					// output the result at the end of the round
	void updateScore();									// update total score and round score
	bool isHuman() const;								// return true if the object is HumanPlayer
	bool has7S() const;									// return true if the hand has 7S
	bool isLegalMoves(const Card&) const;				// return true if card is in legal moves
	bool hasLegalMoves() const;							// return true if the size of leagl moves is not 0

protected:
	Player(int, ModelFacade*, bool);

	void removeFromHand(Card&); 						// remove a specific card from my hand
	Card removeFirstFromHand(); 						// remove the first card from my hand
	Card removeFirstFromLegalMove(); 					// remove the first card from my legal moves

	ModelFacade* getModel() const;								// (internal) getter for the game pointer
	void setScore(int);									// (internal) setter for the round score 
	void addListOfDiscards(Card&);						// add card to the list of discards

private:
	ModelFacade* model_;
	Hand hand_;
	int number_;
	int score_;
	int totalScore_;
	bool isHuman_;
	std::vector<Card> legalMoves_;
	std::vector<Card> listOfDiscards_;
};

#endif