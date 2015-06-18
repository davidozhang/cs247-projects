#include <vector>
#include <iostream>
#include "Hand.h"
#include "Card.h"
#include "Player.h"
#include "Game.h"
using namespace std;

Player::Player(int number, int score, int totalScore, Game* game, bool isHuman): 
	number_(number), score_(score), totalScore_(totalScore), game_(game), isHuman_(isHuman) {}

Player::~Player() {
	game_=NULL;
}

Hand Player::getHand() const {
	return hand_;
}

void Player::setHand(Hand &hand) {
	 hand_ = hand;
}

void Player::setScore(int score) {
	score_ = score;
}

void Player::setLegalMoves(const vector<Card> &legalSet) {
	legalMoves_.clear();

	vector<Card> handCards = hand_.getCards();
	int handSize = handCards.size();
	vector<Card>::const_iterator iter;

	for (int i=0; i<handSize; ++i) {
		for (iter = legalSet.cbegin(); iter != legalSet.cend(); ++iter) {
			if (handCards[i] == *iter) {
				legalMoves_.push_back(handCards[i]); break;
			}
		}
	}
}

void Player::addListOfDiscards(Card &card) {
	listOfDiscards_.push_back(card);
}

void Player::clearListOfDiscards() {
	listOfDiscards_.clear();
}

void Player::removeFromHand(Card &card) {
	hand_.remove(card);
}

Card Player::removeFirstFromHand() {
	return hand_.removeFirst();
}

Card Player::removeFirstFromLegalMove() {
	hand_.remove(legalMoves_[0]);
	return legalMoves_[0];
}

int Player::getScore() const {
	return score_;
}

int Player::getTotalScore() const {
	return totalScore_;
}

int Player::getNumber() const {
	return number_;
}

Game* Player::getGame() const {
	return game_;
}

void Player::outputRoundEndResult() const {
	int size = listOfDiscards_.size();

	cout << "Player " << number_ << "'s discards: "; 
	for (int i=0; i<size; ++i)
		cout << listOfDiscards_[i] << " ";
	cout << endl;

	cout << "Player " << number_ << "'s score: "; 
	cout << totalScore_ << " + " << score_ << " = " << totalScore_+score_ << endl;
}


void Player::updateScore() {
	totalScore_ += score_;
	score_ = 0;
}

bool Player::isHuman() const { return isHuman_; }

bool Player::has7S() const {
	Card temp(SPADE,SEVEN);
	return hand_.hasCard(temp);
}

bool Player::isLegalMoves(const Card &card) const {
	int size = legalMoves_.size();
	for (int i=0; i<size; ++i) {
		if (legalMoves_[i] == card)
			return true;
	}
	return false;
}

bool Player::hasLegalMoves() const {
	return legalMoves_.size() != 0;
}


ostream &operator<<(ostream & sout, const Player &player) {
	sout << "Your hand: " << player.hand_ << endl;
	sout << "Legal plays: ";

	int size = player.legalMoves_.size();
	for (int i=0; i<size; ++i)
		sout << player.legalMoves_[i] << " ";
	sout << endl;
	return sout;
}