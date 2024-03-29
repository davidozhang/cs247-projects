#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"
#include "Card.h"
#include "Table.h"
#include <vector>

// class Table;

class ComputerPlayer: public Player {
public:
	ComputerPlayer(int, Table*);
	virtual void play(Card&);		// computer plays card
	virtual void discard(Card&);	// computer discards card
};

#endif