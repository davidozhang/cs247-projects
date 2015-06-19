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
	Deck* getDeck();
	void startRound();
	bool hasWinner() const;
	std::string getWinners() const;
	Table* getTable();
	void createPlayers();
	void declareWinner();
	void round();
	void notify(Card&);
private:
	Player** players_;
	Deck* deck_;
	Table* table_;
};


#endif