#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <iostream>
#include <string>
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

	void setHand(Hand*);
	void setLegalMoves(const std::vector<Card>&); // used to update the set of legal moves everytime someone make a play
	void clearListOfDiscards(); // used to clear the list of discards at the e nd of each round
	void removeFromHand(Card&); // used to remove a specific card from my hand
	Card removeFirstFromHand(); // used to remove the first card from my hand
	Card removeFirstFromLegalMove(); // used to remove the first card from my legal moves


	Hand* getHand() const;
	Game* getGame() const;
	int getScore() const;
	int getNumber() const;
	std::vector<Card> getLegalMoves() const;
	std::vector<Card> getListOfDiscards() const;
	void outputRoundEndResult() const;
	void updateScore();

	bool isHuman() const;
	bool has7S() const;

	bool isLegalMoves(const Card&) const;
	bool hasLegalMoves() const;

protected:
	Player(int, int, int, Game*, bool);
	void setScore(int);
	void addListOfDiscards(Card&);

private:
	Game* game_;
	Hand* hand_;
	int number_;
	int score_;
	int prevScore_;
	bool isHuman_;
	std::vector<Card> legalMoves_;
	std::vector<Card> listOfDiscards_;
};

std::ostream &operator<<(std::ostream &, const Player &);

#endif