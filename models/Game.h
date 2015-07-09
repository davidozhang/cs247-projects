#ifndef _GAME_
#define _GAME_

#include "Deck.h"
#include "Player.h"
#include "Table.h"
#include <string>

class Player;

class Game {
public:
	Game(int);
	~Game();
	bool hasWinner() const;		// return true if any player has score >= 80
	void createPlayers();		// initialize 4 players at the beginning of the game
	void declareWinner();		// output who is(are) the winner(s)
	void round();				// one round of game; stop when hasWinner() == true
	void notify(Card&);			// used by Player->play(); when played a card, it should add to the table

private:
	Player** players_;
	Deck* deck_;
	Table* table_;
};


#endif