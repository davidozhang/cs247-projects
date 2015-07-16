#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <iostream>
#include "Hand.h"
#include "Card.h"
#include "Table.h"


// class Table;

class Player {
	friend std::ostream &operator<<(std::ostream &, const Player &);

public:

	virtual void play(Card&);
	virtual void discard(Card&);
	virtual ~Player() {}

	void setHand(Hand&);								// setter for hand
	void setTable(Table*);
	void setLegalMoves(const std::vector<Card>&);		// setter for updating the set of legal moves
	void setListOfDiscards(const std::vector<Card>&); 	// setter for the list of discards
	void setListOfPlayedCards(const std::vector<Card>&);

	Hand getHand() const;								// getter for hand
	std::vector<Card> getListOfDiscards() const;		// getter for list of discards card
	std::vector<Card> getListOfPlayedCards() const;
	std::vector<Card> getLegalMoves() const;
	std::string getListOfDiscardsString() const;
	std::string getListOfPlayedCardsString() const;
	int getRoundScore() const;

	void clearListOfDiscards(); 						// clear the list of discards
	void clearListOfPlayedCards();
	bool isHuman() const;								// return true if the object is HumanPlayer
	bool has7S() const;									// return true if the hand has 7S
	bool isLegalMoves(const Card&) const;				// return true if card is in legal moves
	bool hasLegalMoves() const;							// return true if the size of leagl moves is not 0
	void outputRoundDiscards() const;

protected:
	Player(int, Table*, bool);

	void removeFromHand(Card&); 						// remove a specific card from my hand
	Card removeFirstFromHand(); 						// remove the first card from my hand
	Card removeFirstFromLegalMove(); 					// remove the first card from my legal moves

private:
	Table* table_;
	Hand hand_;
	int number_;
	bool isHuman_;
	std::vector<Card> legalMoves_;
	std::vector<Card> listOfDiscards_;
	std::vector<Card> playedCards_;
};

#endif