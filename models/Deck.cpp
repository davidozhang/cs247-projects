#include "Deck.h"
#include "Card.h"
#include <random>
#include <iostream>
#include <vector>

using namespace std;

Deck::Deck(int seed_num) {
	seed=seed_num;
	string suits = "CDHS", ranks = "A234567891JQK";
	for (int i=0; i<suits.length();i++) {
		for (int j=0; j<ranks.length();j++) {
			Suit suit = (Suit)suits.find(suits[i]);
			Rank rank = (Rank)ranks.find(ranks[j]);
			cards_.push_back(Card(suit, rank));
		}
	}
}

vector<Card> Deck::getHand(int player_num) {
	vector<Card> sub_vector(cards_.begin()+13*(player_num-1), cards_.begin()+13*player_num);
	return sub_vector;
}

void Deck::shuffle() {
	static mt19937 rng(seed);

	int n = CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (rng() % n);
		--n;
		Card c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}

void Deck::setSeed(int newseed) {
	seed = newseed;
}

int Deck::getSeed() const {
	return seed;
}

ostream &operator<<(std::ostream& sout, const Deck& d) {
	for (int i=0; i<d.CARD_COUNT; i++) {
		if (i!=0 && i!=d.CARD_COUNT-1 && i%13==0) {
			sout<<endl;
		}
		else if (i!=0) {
			sout<<" ";
		}
		sout<<d.cards_[i];
	}
	sout<<endl;
	return sout;
}