#include "Hand.h"
#include "Deck.h"

Hand::Hand(Deck& deck, int player_num) {
	cards_ = deck.getHand(player_num);
}
