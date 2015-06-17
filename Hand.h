#ifndef _HAND_
#define _HAND_

#include "Card.h"
#include "Deck.h"
#include <vector>

class Hand {
public:
	Hand(Deck&, int);
	void remove(Card&);
	Card* removeFirst();
	std::vector<Card*> getCards() const;
private:
	std::vector<Card*> cards_;
};

#endif