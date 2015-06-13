#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <string>

class Player {
private:
	Hand hand_;
	int number_;
	int score_;
	std::vector<Card*> legalMoves_;
public:
	Player();
	virtual void play(Card*) =0;
	virtual void discard(Card*) =0;
};

std::ostream &operator<<(std::ostream &, const Player &);

#endif