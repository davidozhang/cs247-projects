#include <vector>
#include <iostream>
#include "Hand.h"
#include "Card.h"
#include "Player.h"
#include "HumanPlayer.h"
using namespace std;


HumanPlayer::HumanPlayer(int number, int score): Player(number, score) {}

void HumanPlayer::play(Card &card) {
	hand_->remove(card);
	cout << "Player " << number_ << " plays " << card << "." << endl;

	
	//	g.notify(card);
	
	
}

void HumanPlayer::discard(Card &card) {
	hand_->remove(card);
	cout << "Player " << number_ << " discards " << card << "." << endl;
	score_ += (card.getRank() + 1);

	//	add to discards vector
}