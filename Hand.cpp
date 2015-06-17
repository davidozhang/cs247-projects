#include <vector>
#include "Hand.h"
#include "Deck.h"

Hand::Hand(Deck& deck, int player_num) {
	cards_ = deck.getHand(player_num);
}

void Hand::remove(Card &card) {
	int size = cards_.size();
	for (int i=0; i<size; ++i) {
		if (*cards_[i] == card) {
			cards_.erase(cards_.begin() + i); break;
		}
	}
}

Card* Hand::removeFirst() {
	Card* temp = cards_[0];
	cards_.erase(cards_.begin());
	return temp;
}

vector<Card*> Hand::getCards() const { return cards_; }