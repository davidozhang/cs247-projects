#include "Table.h"
#include "Card.h"
#include <iostream>
#include <algorithm>

using namespace std;

Table::Table() {}

void Table::getLegalCardsHelper(vector<Card>& result, vector<Card>& traverse, Suit suit) {
	if (!traverse.empty() && traverse[0].getRank()>0) {
		result.push_back(Card(suit, (Rank)(traverse[0].getRank()-1)));
	}
	if (!traverse.empty() && traverse[traverse.size()-1].getRank()<12) {
		result.push_back(Card(suit, (Rank)(traverse[traverse.size()-1].getRank()+1)));
	}
}

vector<Card> Table::getLegalCards() {
	vector<Card> result;
	getLegalCardsHelper(result, clubs_, CLUB);
	getLegalCardsHelper(result, diamonds_, DIAMOND);
	getLegalCardsHelper(result, hearts_, HEART);
	getLegalCardsHelper(result, spades_, SPADE);
	result.push_back(Card(SPADE, SEVEN));
	result.push_back(Card(CLUB, SEVEN));
	result.push_back(Card(DIAMOND, SEVEN));
	result.push_back(Card(HEART, SEVEN));
	return result;
}

void Table::addCard(Card& card) {
	if (card.getSuit()==CLUB) {
		clubs_.push_back(card);
		std::sort(clubs_.begin(), clubs_.end());
	} else if (card.getSuit()==DIAMOND) {
		diamonds_.push_back(card);
		std::sort(diamonds_.begin(), diamonds_.end());
	} else if (card.getSuit()==HEART) {
		hearts_.push_back(card);
		std::sort(hearts_.begin(), hearts_.end());
	} else if (card.getSuit()==SPADE) {
		spades_.push_back(card);
		std::sort(spades_.begin(), spades_.end());
	}
}

void Table::clear() {
	clubs_.clear();
	diamonds_.clear();
	hearts_.clear();
	spades_.clear();
}

string Table::listCards(const vector<Card>& v) const {
	string output="";
	string str_rank[] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
	vector<Card> temp=v;
	vector<Card>::iterator it;
	for (it=temp.begin();it!=temp.cend();it++) {
		output+=" "+str_rank[(*it).getRank()];
	}
	return output;
}



/* Temp method */
vector<Card> Table::getCardsOnTable() const {
	vector<Card> result;
	return result;
}

std::ostream &operator<<(std::ostream& sout, const Table& table) {
	sout<<"Cards on the table:"<<endl;
	sout<<"Clubs:"<< table.listCards(table.clubs_)<<endl;
	sout<<"Diamonds:"<< table.listCards(table.diamonds_)<<endl;
	sout<<"Hearts:" << table.listCards(table.hearts_)<<endl;
	sout<<"Spades:"<< table.listCards(table.spades_)<<endl;
	return sout;
}