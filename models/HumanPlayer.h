#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "Player.h"
#include "Card.h"
#include "Game.h"
#include <vector>

class HumanPlayer: public Player {
public:
	HumanPlayer(int, int, int, Game*);
	virtual void play(Card&);
	virtual void discard(Card&);
};

#endif