#ifndef _DECK_
#define _DECK_

#include "Card.h"
#include <vector>

class Deck {
public:
	Deck(int);
	std::vector<Card> getHand(int player_num);						// return a vector of card based on player number
	friend std::ostream &operator<<(std::ostream &, const Deck&);
	void shuffle();
	void setSeed(int);
	int getSeed() const;
private:
	int seed;
	static const int CARD_COUNT=52;
	std::vector<Card> cards_;
};

#endif