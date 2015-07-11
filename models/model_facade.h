#ifndef _MODELFACADE_
#define _MODELFACADE_

#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Table.h"
#include "Player.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

#include <vector>

class ModelFacade: public Subject {
private:
	vector<Player*> players_(4, NULL);
	vector<int> scores_(4, 0);

	Deck* deck_;
	Table* table_;
public:
	ModelFacade();
	startGame(int); // start a game with seed
	setPlayerType(int, string);
	selectCard(int, Card); 
};