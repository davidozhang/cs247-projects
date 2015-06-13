#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include <vector>

class HumanPlayer: public Player {
public:
	HumanPlayer();
	virtual void play(Card*);
	virtual void discard(Card*);
	void quit();
	void ragequit();
};

std::ostream &operator<<(std::ostream &, const Player &);

#endif