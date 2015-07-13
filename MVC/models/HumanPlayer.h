#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "Player.h"
#include "Card.h"
#include "model_facade.h"
#include <vector>

class ModelFacade;

class HumanPlayer: public Player {
public:
	HumanPlayer(int, ModelFacade*);
	virtual void play(Card&);
	virtual void discard(Card&);
};

#endif