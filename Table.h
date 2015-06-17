#ifndef _TABLE_
#define _TABLE_

#include "Card.h"
#include <vector>
#include <string>

class Table {
public:
	void addCard(Card&);
	friend std::ostream &operator<<(std::ostream &, const Table &);
private:
	std::string listCards(const std::vector<Card>&) const;
	std::vector<Card> clubs_;
	std::vector<Card> diamonds_;
	std::vector<Card> hearts_;
	std::vector<Card> spades_;
};

#endif