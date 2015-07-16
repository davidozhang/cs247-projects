#include <vector>
#include <iostream>
#include "Hand.h"
#include "Card.h"
#include "Player.h"
#include "Table.h"
#include "HumanPlayer.h"
using namespace std;


HumanPlayer::HumanPlayer(int number, Table* table): Player(number, table, true) {}

void HumanPlayer::play(Card &card) {
	removeFromHand(card);
	Player::play(card);
}

void HumanPlayer::discard(Card &card) {
	removeFromHand(card);
	Player::discard(card);
}
