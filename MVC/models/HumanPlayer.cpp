#include <vector>
#include <iostream>
#include "Hand.h"
#include "Card.h"
#include "Player.h"
#include "model_facade.h"
#include "HumanPlayer.h"
using namespace std;


HumanPlayer::HumanPlayer(int number, ModelFacade* model): Player(number, model, true) {}

void HumanPlayer::play(Card &card) {
	removeFromHand(card);
	// cout << "Player " << getNumber() << " plays " << card << "." << endl;
	getModel()->addCardToTable(card);
}

void HumanPlayer::discard(Card &card) {
	removeFromHand(card);
	// cout << "Player " << getNumber() << " discards " << card << "." << endl;
	addListOfDiscards(card);
}
