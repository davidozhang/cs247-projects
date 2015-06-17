#include <vector>
#include <iostream>
#include <set>
#include "Hand.h"
#include "Card.h"
#include "Player.h"
using namespace std;

Player::Player(int number, int score): number_(number), score_(score) {}

void Player::setHand(const Hand *hand): hand_(hand) {}

int Player::getScore() const { return score_; }

bool Player::isHuman() const { return isHuman_; }



void Player::setLegalMoves(const set<Card*> &legalSet) {
	legalMoves_.clear();

	vector<Card*> handCards = hand_.getCards();
	int handSize = handCards.size();
	set<Card*>::iterator iter;

	for (int i=0; i<handSize; ++i) {
		for (iter = legalSet.begin(); iter != legalSet.end(); ++iter) {
			if (*handCards[i] == **iter) {
				legalMoves_.push_back(handCards[i]); break;
			}
		}
	}
}

ostream &operator<<(ostream & sout, const Player &player) {
	sout << "Your hand: " << *(player.hand_) << endl;
	sout << "Legal plays: ";

	int size = player.legalMoves_.size();
	for (int i=0; i<size; ++i)
		cout << *(player.legalMoves_[i]) << " ";
	cout << endl;
}
