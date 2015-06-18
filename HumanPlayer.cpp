#include <vector>
#include <iostream>
#include "Hand.h"
#include "Card.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "Game.h"
using namespace std;


HumanPlayer::HumanPlayer(int number, int score, int prevScore, Game* game): Player(number, score, prevScore, game, true) {}

void HumanPlayer::play(Card &card) {
	removeFromHand(card);
	cout << "Player " << getNumber() << " plays " << card << "." << endl;
	getGame()->notify(card);
}

void HumanPlayer::discard(Card &card) {
	removeFromHand(card);
	cout << "Player " << getNumber() << " discards " << card << "." << endl;
	setScore(getScore() + card.getRank() + 1);
	addListOfDiscards(card);
}
