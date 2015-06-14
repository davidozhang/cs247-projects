#ifndef _GAME_
#define _GAME_

#include <set>

class Game {
public:
	Game();
	~Game();
	Deck* getDeck();
private:
	//Player players_[4];
	Deck deck_;
	//set<Card*> legalCards_;
};


#endif