#include <vector>
#include <iostream>
#include "Hand.h"
#include "Card.h"
#include "Player.h"
#include "model_facade.h"
#include "ComputerPlayer.h"
using namespace std;

ComputerPlayer::ComputerPlayer(int number, ModelFacade* model): Player(number, model, false) {}

void ComputerPlayer::play(Card &dummy) {
	Card card = removeFirstFromLegalMove();
	// cout << "Player " << getNumber() << " plays " << card << "." << endl;
	getModel()->addCardToTable(card);
}

void ComputerPlayer::discard(Card &dummy) {
	Card card = removeFirstFromHand();
	// cout << "Player " << getNumber() << " discards " << card << "." << endl;
	addListOfDiscards(card);
}