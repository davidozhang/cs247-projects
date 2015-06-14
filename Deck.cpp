#include "Card.h"
#include <random>
#include <iostream>
#include <vector>

using namespace std;

class Deck {
public:
	Deck(int);
	int getCardCount() const;
	vector<Card*> getCards();
	friend ostream &operator<<(std::ostream& sout, const Deck& d);
private:
	void shuffle();
	int seed;
	static const int CARD_COUNT=52;
	vector<Card*> cards_;
};

Deck::Deck(int seed_num) {
	seed=seed_num;
	string suits = "CDHS", ranks = "A234567891JQK";
	int counter=0;
	for (int i=0; i<ranks.length();i++) {
		for (int j=0; j<suits.length();j++) {
			Rank rank = (Rank)ranks.find(ranks[i]);
			Suit suit = (Suit)suits.find(suits[j]);
			cards_.push_back(new Card(suit, rank));
		}
	}
	shuffle();
}

int Deck::getCardCount() const{
	return CARD_COUNT;
}

void Deck::shuffle() {
	static mt19937 rng(seed);

	int n = CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (rng() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}

ostream &operator<<(std::ostream& sout, const Deck& d) {
	for (int i=0; i<d.getCardCount(); i++) {
		if (i!=0 && i!=d.getCardCount()-1 && i%13==0) {
			sout<<endl;
		}
		else if (i!=0) {
			sout<<" ";
		}
		sout<<*(d.cards_[i]);
	}
	return sout;
}