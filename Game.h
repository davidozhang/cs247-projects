#ifndef _GAME_
#define _GAME_

#include "Deck.h"
#include "Player.h"
#include "Table.h"
#include <string>
#include <vector>

class Player;

class Game {
public:
	Game(int);
	~Game();
	Deck* getDeck();
	void newPlayer(int, std::string);
	void startRound();
	bool hasPlayer() const;
	std::string getWinners() const;
	Table* getTable();


	void createPlayers();
	void round();
private:
	Player** players_;
	Deck* deck_;
	Table* table_;
};


#endif