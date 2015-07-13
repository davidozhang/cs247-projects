#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"
#include "Card.h"
#include "model_facade.h"
#include <vector>

class ModelFacade;

class ComputerPlayer: public Player {
public:
	ComputerPlayer(int, ModelFacade*);
	virtual void play(Card&);
	virtual void discard(Card&);
};

#endif