#include <vector>
#include <iostream>
#include "Hand.h"
#include "Card.h"
#include "Player.h"
#include "Table.h"
using namespace std;

namespace {
	string suits[SUIT_COUNT] = {"C", "D", "H", "S"};
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
}


Player::Player(int number, Table* table, bool isHuman): number_(number), table_(table), isHuman_(isHuman) {}


/*----------------------------------------------
	Getters and Setters
----------------------------------------------*/

Hand Player::getHand() const { return hand_; }

void Player::setHand(Hand &hand) { hand_ = hand; }

void Player::setTable(Table* table) {table_ = table; }

void Player::setListOfDiscards(const vector<Card> &discards) { listOfDiscards_ = discards; }

void Player::setListOfPlayedCards(const vector<Card> &cards) { playedCards_ = cards; }

vector<Card> Player::getListOfDiscards() const { return listOfDiscards_; }

vector<Card> Player::getListOfPlayedCards() const { return playedCards_; }

vector<Card> Player::getLegalMoves() const {return legalMoves_; }


/*----------------------------------------------
	Main methods
----------------------------------------------*/

void Player::play(Card& card) {
	cout << "Player " << number_ << " plays " << card << "." << endl;
	table_->addCard(card);
	playedCards_.push_back(card);
}

void Player::discard(Card& card) {
	cout << "Player " << number_ << " discards " << card << "." << endl;
	listOfDiscards_.push_back(card);
}

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
	Clear the list of discards
*/
void Player::clearListOfDiscards() {
	listOfDiscards_.clear();
}

void Player::clearListOfPlayedCards() {
	playedCards_.clear();
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

int Player::getRoundScore() const {
	int score = 0;
	int size = listOfDiscards_.size();
	for (int i=0; i<size; ++i) {
		score += (listOfDiscards_[i].getRank() + 1);
	}
	return score;
}

string Player::getListOfDiscardsString() const {
	string result = "";
	int size = listOfDiscards_.size();

	result += ("Player " + to_string(number_) + "'s discards:"); 
	for (int i=0; i<size; ++i)
		result += (" " + ranks[listOfDiscards_[i].getRank()] + suits[listOfDiscards_[i].getSuit()]);
	result += "\n";

	return result;
}

string Player::getListOfPlayedCardsString() const {
	string result = "";
	int size = playedCards_.size();

	result += ("Player " + to_string(number_) + "'s played cards:"); 
	for (int i=0; i<size; ++i)
		result += (" " + ranks[playedCards_[i].getRank()] + suits[playedCards_[i].getSuit()]);
	result += "\n";

	return result;
}

void Player::outputRoundDiscards() const {
	int size = listOfDiscards_.size();

	cout << "Player " << number_ << "'s discards:"; 
	for (int i=0; i<size; ++i)
		cout << " " << listOfDiscards_[i];
	cout << endl;
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