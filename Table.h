#ifndef _TABLE_
#define _TABLE_

#include <set>

class Table {
private:
	set<Card*> diamonds_;
	set<Card*> hearts_;
	set<Card*> spades_;
	set<Card*> clubs_;
public:
	Table();
};

std::ostream &operator<<(std::ostream &, const Table &);


#endif