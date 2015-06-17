#ifndef _GAME_
#define _GAME_

#include "Deck.h"
#include "Player.h"
#include "Table.h"
#include <set>
#include <string>

class Game {
public:
	Game(int);
	~Game();
	Deck* getDeck();
	void newPlayer(int, std::string);
	void startRound();
	bool hasPlayer() const;
	std::string getWinners() const;
private:
	Player players_[4];
	Deck* deck_;
	Table* table_;
	// vector<Card*> legalCards_;
};


#endif