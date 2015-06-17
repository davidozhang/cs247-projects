#include <vector>
#include <iostream>
#include "Hand.h"
#include "Card.h"
#include "Player.h"
using namespace std;

Player::Player(int number, int score): number_(number), score_(score) {}

Player::setHand(Hand *hand): hand_(hand) {}

Hand* Player::getHand() const { return hand_; }

vector<Card*> Player::getLegalMoves() const { return legalMoves; }

ostream &operator<<(ostream & sout, const Player &player) {
	sout << "Your hand: " << *player.getHand() << endl;
	sout << "Legal plays: ";

	vector<Card*> temp = player.getLegalMoves();
	for (int i=0; i<temp.size(); ++i)
		cout << *temp[i] << " ";
	cout << endl;
}
