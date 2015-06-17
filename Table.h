#ifndef _TABLE_
#define _TABLE_

#include "Card.h"
#include <set>

class Table {
private:
	std::set<Card*> diamonds_;
	std::set<Card*> hearts_;
	std::set<Card*> spades_;
	std::set<Card*> clubs_;
public:
	Table();

	std::set<Card*> getLegalCards() const;
};

std::ostream &operator<<(std::ostream &, const Table &);


#endif