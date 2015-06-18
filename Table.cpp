#include "Table.h"
#include "Card.h"
#include <iostream>
#include <algorithm>

using namespace std;

Table::Table() {
	legalCards_.push_back(new Card(SPADE, SEVEN));
	legalCards_.push_back(new Card(CLUB, SEVEN));
	legalCards_.push_back(new Card(DIAMOND, SEVEN));
	legalCards_.push_back(new Card(HEART, SEVEN));
}

void Table::addCard(Card& card) {
	if (card.getSuit()==CLUB) {
		clubs_.push_back(card);
	} else if (card.getSuit()==DIAMOND) {
		diamonds_.push_back(card);
	} else if (card.getSuit()==HEART) {
		hearts_.push_back(card);
	} else if (card.getSuit()==SPADE) {
		spades_.push_back(card);
	}
}

string Table::listCards(const vector<Card>& v) const {
	string output="";
	string str_rank[] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
	vector<Card> temp=v;
	vector<Card>::iterator it;
	for (int i=0; i<13; i++) {
		for (it=temp.begin();it!=temp.cend();it++) {
			if ((*it).getRank()==i) {
				output+=" "+str_rank[(*it).getRank()];
			}
		}
	}
	return output;
}

std::ostream &operator<<(std::ostream& sout, const Table& table) {
	sout<<"Cards on the table:"<<endl;
	sout<<"Clubs:"<< table.listCards(table.clubs_)<<endl;
	sout<<"Diamonds:"<< table.listCards(table.diamonds_)<<endl;
	sout<<"Hearts:" << table.listCards(table.hearts_)<<endl;
	sout<<"Spades:"<< table.listCards(table.spades_)<<endl;
	return sout;
}