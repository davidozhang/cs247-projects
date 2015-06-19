#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"
#include "Card.h"
#include "Game.h"
#include <vector>

class ComputerPlayer: public Player {
public:
	ComputerPlayer(int, int, int, Game*);
	virtual void play(Card&);
	virtual void discard(Card&);
};

#endif