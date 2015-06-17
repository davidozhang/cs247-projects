#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <iostream>
#include <set>
#include <string>
#include "Hand.h"
#include "Card.h"


class Player {
	friend std::ostream &operator<<(std::ostream &, const Player &);

public:
	Player(int, int);
	virtual void play(Card&) =0;
	virtual void discard(Card&) =0;

	void setHand(const Hand*);
	void setLegalMoves(const std::set<Card*>&);
	int getScore() const;
	bool isHuman() const;
	bool has7S() const;
};

private:
	Hand *hand_;
	int number_;
	int score_;
	bool isHuman_;
	std::vector<Card*> legalMoves_;
	std::vector<Card*> listOfDiscards_;

std::ostream &operator<<(std::ostream &, const Player &);

#endif