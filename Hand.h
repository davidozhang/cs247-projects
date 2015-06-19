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
	void remove(Card&);						// remove card from hand
	Card removeFirst();						// remove the first card from hand
	bool hasCard(Card&) const;				// return true if my hand has this card
	std::vector<Card> getCards() const;		// return the list of cards in my hand
private:
	std::vector<Card> cards_;
};

#endif