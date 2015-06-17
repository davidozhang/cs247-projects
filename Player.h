#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <iostream>

class Player {
private:
	Hand *hand_;
	int number_;
	int score_;
	std::vector<Card*> legalMoves_;
public:
	Player(int);
	virtual void play(Card*) =0;
	virtual void discard(Card*) =0;
	void setHand(Hand*);
	Hand* getHand() const;
	vector<Card*> getLegalMoves() const;
};

std::ostream &operator<<(std::ostream &, const Player &);

#endif