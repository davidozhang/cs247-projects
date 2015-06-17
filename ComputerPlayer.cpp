#include <vector>
#include <iostream>
#include "Hand.h"
#include "Card.h"
#include "Player.h"
#include "ComputerPlayer.h"
using namespace std;



ComputerPlayer::ComputerPlayer(int number, int score): Player(number, score), Player::isHuman_(false) {}

void ComputerPlayer::play(Card &dummy) {
	if (legalMoves_.size() != 0) {
		Card* card = hand_->removeFirst();
		cout << "Player " << number_ << " plays " << *card << "." << endl;

		//	g.notify(card);
	} else {
		Card* card = hand_->removeFirst();
		cout << "Player " << number_ << " discards " << *card << "." << endl;
		score_ += (card.getRank() + 1);

		//	add to discards vector
	}
}

void ComputerPlayer::discard(Card &dummy) {}