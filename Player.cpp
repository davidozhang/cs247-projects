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

/*----------------------------------------------
	Getters and Setters
----------------------------------------------*/

Hand Player::getHand() const { return hand_; }

void Player::setHand(Hand &hand) { hand_ = hand; }

void Player::setScore(int score) { score_ = score; }

void Player::setListOfDiscards(const vector<Card> &discards) { listOfDiscards_ = discards; }

int Player::getScore() const { return score_; }

int Player::getTotalScore() const { return totalScore_; }

int Player::getNumber() const { return number_; }

Game* Player::getGame() const { return game_; }

vector<Card> Player::getListOfDiscards() const { return listOfDiscards_; }


/*----------------------------------------------
	Main methods
----------------------------------------------*/

/*
	Set the legal moves based on the lagel set passed from Table
*/
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

/*
	Add the card to the list of discards
*/
void Player::addListOfDiscards(Card &card) {
	listOfDiscards_.push_back(card);
}

/*
	Clear the list of discards
*/
void Player::clearListOfDiscards() {
	listOfDiscards_.clear();
}

/*
	Remove the card from my hand
*/
void Player::removeFromHand(Card &card) {
	hand_.remove(card);
}

/*
	Remove the frist card from my hand
*/
Card Player::removeFirstFromHand() {
	return hand_.removeFirst();
}

/*
	Remove the first card in legal moves
*/
Card Player::removeFirstFromLegalMove() {
	hand_.remove(legalMoves_[0]);
	return legalMoves_[0];
}

/*
	Output the result of the round at the end
*/
void Player::outputRoundEndResult() const {
	int size = listOfDiscards_.size();

	cout << "Player " << number_ << "'s discards:"; 
	for (int i=0; i<size; ++i)
		cout << " " << listOfDiscards_[i];
	cout << endl;

	cout << "Player " << number_ << "'s score: "; 
	cout << totalScore_ << " + " << score_ << " = " << totalScore_+score_ << endl;
}

/*
	Update the score and total score at the end of the round
*/
void Player::updateScore() {
	totalScore_ += score_;
	score_ = 0;
}

/*
	Return true if this is human player
*/
bool Player::isHuman() const { 
	return isHuman_;
}

/*
	Return true if my hand has 7S
*/
bool Player::has7S() const {
	Card temp(SPADE,SEVEN);
	return hand_.hasCard(temp);
}

/*
	Return true if card is in the legal moves
*/
bool Player::isLegalMoves(const Card &card) const {
	int size = legalMoves_.size();
	for (int i=0; i<size; ++i) {
		if (legalMoves_[i] == card)
			return true;
	}
	return false;
}

/*
	Return true if I have at least one legal move
*/
bool Player::hasLegalMoves() const {
	return legalMoves_.size() != 0;
}

/*
	Out stream operator
*/
ostream &operator<<(ostream & sout, const Player &player) {
	sout << "Your hand:" << player.hand_ << endl;
	sout << "Legal plays:";

	int size = player.legalMoves_.size();
	for (int i=0; i<size; ++i)
		sout << " " << player.legalMoves_[i];
	sout << endl;
	return sout;
}