#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "Player.h"
#include "Card.h"
#include <vector>

class HumanPlayer: public Player {
public:
	HumanPlayer(int);
	virtual void play(Card&);
	virtual void discard(Card&);
};


#endif