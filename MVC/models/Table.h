#ifndef _TABLE_
#define _TABLE_

#include "Card.h"
#include <vector>
#include <string>

class Table {
	friend std::ostream &operator<<(std::ostream &, const Table &);
public:
	Table();
	void addCard(Card&);				// add card to the table
	std::vector<Card> getLegalCards();	// get legal cards set based on the cards on the table
	void clear();						// clear the table

	std::vector<Card> getCardsOnTable() const;
private:
	void getLegalCardsHelper(std::vector<Card>&, std::vector<Card>&, Suit);
	std::string listCards(const std::vector<Card>&) const;
	std::vector<Card> clubs_;
	std::vector<Card> diamonds_;
	std::vector<Card> hearts_;
	std::vector<Card> spades_;
};

#endif