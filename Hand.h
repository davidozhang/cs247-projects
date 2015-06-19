#ifndef _HAND_
#define _HAND_

#include "Card.h"
#include "Deck.h"
#include <vector>

class Hand {
	friend std::ostream &operator<<(std::ostream &sout, const Hand &hand);
public:
	Hand();
	Hand(Deck&, int);
	void remove(Card&);
	Card removeFirst();
	bool hasCard(Card&) const;
	std::vector<Card> getCards() const;
private:
	std::vector<Card> cards_;
};

#endif