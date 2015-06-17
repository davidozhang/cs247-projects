#include <vector>
#include <iostream>
#include "Hand.h"
#include "Card.h"
#include "Player.h"
#include "ComputerPlayer.h"
using namespace std;



ComputerPlayer::ComputerPlayer(int number, int score): Player(number, score) {}

void ComputerPlayer::play(Card &dummy) {
	if (legalMoves_.size() != 0) {
		Card* card = hand_->removeFirst();
		cout << "Player " << number_ << " plays " << *card << "." << endl;
	} else {
		Card* card = hand_->removeFirst();
		cout << "Player " << number_ << " discards " << *card << "." << endl;
		score_ += (card.getRank() + 1);
	}
}

void ComputerPlayer::discard(Card &dummy) {}