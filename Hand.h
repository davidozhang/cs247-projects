#ifndef _HAND_
#define _HAND_

#include "Card.h"
#include "Deck.h"
#include <vector>

class Hand {
	friend std::ostream &operator<<(std::ostream &sout, const Hand &hand);
public:
	Hand(Deck&, int);
	void remove(Card&);
	Card removeFirst();
	std::vector<Card> getCards() const;
	bool hasCard(Card&) const;
private:
	std::vector<Card> cards_;
};

std::ostream &operator<<(std::ostream &, const Hand &);

#endif