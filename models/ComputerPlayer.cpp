#include <vector>
#include <iostream>
#include "Hand.h"
#include "Card.h"
#include "Player.h"
#include "Table.h"
#include "ComputerPlayer.h"
using namespace std;

ComputerPlayer::ComputerPlayer(int number, Table* table): Player(number, table, false) {}

void ComputerPlayer::play(Card &dummy) {
	Card card = removeFirstFromLegalMove();
	Player::play(card);
}

void ComputerPlayer::discard(Card &dummy) {
	Card card = removeFirstFromHand();
	Player::discard(card);
}