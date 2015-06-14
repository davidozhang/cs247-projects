#ifndef _DECK_
#define _DECK_

#include "Card.h"
#include <vector>

class Deck {
public:
	Deck(int);
	~Deck();
	int getCardCount() const;
	friend std::ostream &operator<<(std::ostream &, const Deck&);
private:
	void shuffle();
	int seed;
	static const int CARD_COUNT=52;
	std::vector<Card*> cards_;
};

#endif