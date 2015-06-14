#ifndef _GAME_
#define _GAME_

#include "Deck.h"
#include <set>

class Game {
public:
	Game(int);
	~Game();
	Deck* getDeck();
private:
	//Player players_[4];
	Deck* deck_;
	//set<Card*> legalCards_;
};


#endif