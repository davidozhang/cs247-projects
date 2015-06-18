#ifndef _DECK_
#define _DECK_

#include "Card.h"
#include <vector>

class Deck {
public:
	Deck(int);
	~Deck();
	std::vector<Card*> getHand(int player_num);
	friend std::ostream &operator<<(std::ostream &, const Deck&);
	void shuffle();
private:
	int seed;
	static const int CARD_COUNT=52;
	std::vector<Card*> cards_;
};

#endif