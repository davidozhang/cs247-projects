#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include <vector>

class ComputerPlayer: public Player {
public:
	ComputerPlayer();
	virtual void play(Card*);
	virtual void discard(Card*);
};

std::ostream &operator<<(std::ostream &, const Player &);

#endif