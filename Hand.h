#ifndef _HAND_
#define _HAND_

#include "Card.h"
#include "Deck.h"
#include <vector>

class Hand {
public:
	Hand(Deck&, int);
private:
	std::vector<Card*> cards_;
};

#endif