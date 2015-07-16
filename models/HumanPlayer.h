#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "Player.h"
#include "Card.h"
#include "Table.h"
#include <vector>

// class Tbale;

class HumanPlayer: public Player {
public:
	HumanPlayer(int, Table*);
	virtual void play(Card&);
	virtual void discard(Card&);
};

#endif