#ifndef _DECK_
#define _DECK_

#include "Card.h"
#include <vector>

class Deck {
public:
	Deck(int);
	int getCardCount() const;
private:
	void shuffle();
	static const int CARD_COUNT=52;
	std::vector<Card*> cards_;
};

std::ostream &operator<<(std::ostream &, const Deck&);

#endif