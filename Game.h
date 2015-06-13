#ifndef _GAME_
#define _GAME_

#include <set>

class Game {
private:
	Player players_[4];
	Deck deck_;
	set<Card*> legalCards_;
public:
	Game();
};


#endif