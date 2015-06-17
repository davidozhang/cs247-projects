#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"
#include <vector>

class ComputerPlayer: public Player {
public:
	ComputerPlayer(int);
	virtual void play(Card*);
	virtual void discard(Card*);
};


#endif