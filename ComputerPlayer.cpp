#include <vector>
#include <iostream>
#include "Hand.h"
#include "Card.h"
#include "Player.h"
#include "Game.h"
#include "ComputerPlayer.h"
using namespace std;



ComputerPlayer::ComputerPlayer(int number, int score, int totalScore, Game* game): Player(number, score, totalScore, game, false) {}

void ComputerPlayer::play(Card &dummy) {
	if (hasLegalMoves()) {
		Card card = removeFirstFromLegalMove();
		cout << "Player " << getNumber() << " plays " << card << "." << endl;
		getGame()->notify(card);
	} else {
		Card card = removeFirstFromHand();
		cout << "Player " << getNumber() << " discards " << card << "." << endl;
		setScore(getScore() + card.getRank() + 1);
		addListOfDiscards(card);
	}
}

void ComputerPlayer::discard(Card &dummy) {}