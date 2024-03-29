#include "../observer.h"
#include "view.h"
#include "../controllers/controller.h"
#include "../models/model_facade.h"
#include "../subject.h"
#include "DeckGUI.h"
#include "dialog.h"
#include <iostream>
#include <string>

View::View(Controller *c, ModelFacade *m) : model_(m), controller_(c), main_box(false, 5), clubs_on_table(true, 2), diamonds_on_table(true, 2), hearts_on_table(true, 2), spades_on_table(true, 2), top_panel(false, 10), cards_panel(false, 5), players_panel(false, 5), player_hand_panel(false, 5), legal_panel(false, 5) {
	set_title( "Straights UI - David & Jerry" );
	set_border_width( 10 );
	//
	add(main_box);
	main_box.pack_start(top_panel);
	cards_panel_label.set_label("Cards on the table");
	cards_panel_label.set_alignment(0,0);
	main_box.pack_start(cards_panel_label);
	main_box.pack_start(cards_panel);
	main_box.pack_start(players_panel_labels);
	main_box.pack_start(players_panel);
	player_hand_panel_label.set_label("Your hand");
	player_hand_panel_label.set_alignment(0,0);
	main_box.pack_start(player_hand_panel_label);
	main_box.pack_start(player_hand_panel);
	std::string played_cards_label;
	for (int i=0; i<4; i++) {
		played_cards_label+="Player "+std::to_string(i+1)+"'s played cards:\n";
	}
	played_cards_panel.set_label(played_cards_label);
	played_cards_panel.set_alignment(0,0);
	main_box.pack_start(played_cards_panel);
	legal_panel_label.set_label("Legal moves");
	legal_panel_label.set_alignment(0,0);
	main_box.pack_start(legal_panel_label);
	main_box.pack_start(legal_panel);

	start_button.set_label("Start new game with seed: ");
	top_panel.add(start_button);
	text_field.set_text("0");
	text_field.set_alignment(0.5);
	top_panel.add(text_field);
	end_button.set_label("End current game");
	top_panel.add(end_button);

	for (int i=0; i<13; i++) {
		hand_images[i].set(deck.null());
		club_images[i].set(deck.null());
		diamond_images[i].set(deck.null());
		heart_images[i].set(deck.null());
		spade_images[i].set(deck.null());
		legal_images[i].set(deck.null());
		hand_buttons[i].set_image(hand_images[i]);
		hand_buttons[i].signal_clicked().connect( sigc::bind<int>(sigc::mem_fun(*this, &View::handButtonClicked), i));
		clubs_on_table.add(club_images[i]);
		diamonds_on_table.add(diamond_images[i]);
		hearts_on_table.add(heart_images[i]);
		spades_on_table.add(spade_images[i]);
		legal_panel.add(legal_images[i]);
		player_hand_panel.add(hand_buttons[i]);
	}
	cards_panel.add(clubs_on_table);
	cards_panel.add(diamonds_on_table);
	cards_panel.add(hearts_on_table);
	cards_panel.add(spades_on_table);

	for (int i=0; i<4; i++) {
		human.push_back("h");
		points[i]=0;
		discards[i]=0;
		player_buttons[i].set_label("Human");
		player_buttons[i].signal_clicked().connect( sigc::bind<int>(sigc::mem_fun(*this, &View::playerButtonClicked), i));
		player_stats[i].set_label(std::to_string(points[i])+" points\n"+std::to_string(discards[i])+" discards");
		players[i].add(player_buttons[i]);
		players[i].add(player_stats[i]);
		players_panel.add(players[i]);
		player_panel_label[i].set_label("Player "+std::to_string(i+1));
		players_panel_labels.add(player_panel_label[i]);
	}

	start_button.signal_clicked().connect( sigc::mem_fun( *this, &View::startButtonClicked ) );
	end_button.signal_clicked().connect( sigc::mem_fun( *this, &View::endButtonClicked ) );
	show_all();
	model_->subscribe(this);

} // View::View

View::~View() {}

void View::update(std::string state) {
	int current_player = model_->getCurrentPlayer();
	if (state=="new round") {
		Dialog dialog(*this, "A new round begins. It's player "+std::to_string(current_player+1)+"'s turn to play.");
		setActivePlayerButton(current_player);
		updateAllCards(current_player);
		for (int i=0; i<4; i++) {
			discards[i]=0;
			points[i]=model_->getPoints(i);
		}
		updatePlayerStatsLabels();
		clearTable();
		setPlayedCards(model_->getPlayedCardsString());
	} else if (state=="end round") {
		Dialog dialog(*this, model_->getRoundEndResult());
	} else if (state=="new turn") {
		setActivePlayerButton(current_player);
		updateAllCards(current_player);
		for (int i=0; i<4; i++) {
			discards[i]=model_->getDiscards(i);
		}
		updatePlayerStatsLabels();
		setPlayedCards(model_->getPlayedCardsString());
	} else if (state=="end game") {
		clearHand();
		clearTable();
		clearLegal();
		resetDiscardsAndPoints();
		resetPlayerButtons();
		setPlayedCards(model_->getPlayedCardsString());
	} else if (state=="invalid play") {
		Dialog dialog(*this, "Invalid Move, There are still legal moves.");
	} else if (state=="has winner") {
		std::vector<int> winners;
		model_->getWinners(winners);
		for (int i=0; i<winners.size(); i++) {
			Dialog dialog(*this, "Player "+ std::to_string(winners[i]+1) +" wins!");
		}
	} else {
		//invalid state, should never reach here
	}
}

void View::cardVectorToImages(Gtk::Image* images, std::vector<Card> cards, bool unsorted) {
	for (int i=0; i<cards.size(); i++) {
		if (unsorted) {		//hand doesn't require to be sorted
			if (cards[i].getSuit()==NOSUIT) {
				images[i].set(deck.null());
			} else {
				images[i].set(deck.image(cards[i].getRank(), cards[i].getSuit()));
			}
		} else {
			images[cards[i].getRank()].set(deck.image(cards[i].getRank(), cards[i].getSuit()));
		}
	}
}

void View::startButtonClicked() {
	for (int i=0; i<4; i++) {
		this->player_buttons[i].set_label("Rage!");
	}
	int seed = std::stoi(text_field.get_text());
	controller_->startButtonClicked(seed, human);
}

void View::endButtonClicked() {
	resetPlayerButtons();
	controller_->endButtonClicked();
}

void View::setActivePlayerButton(int active) {
	for (int i=0; i<4; i++) {
		if (i==active) {
			this->player_buttons[i].set_sensitive(true);
		} else {
			this->player_buttons[i].set_sensitive(false);
		}
	}
}

void View::playerButtonClicked(int num) {
	if (this->player_buttons[num].get_label()=="Human") {
		this->player_buttons[num].set_label("Computer");
		human[num]="c";
	} else if (this->player_buttons[num].get_label()=="Computer") {
		this->player_buttons[num].set_label("Human");
		human[num]="h";
	} else if (this->player_buttons[num].get_label()=="Rage!") {
		controller_->rageButtonClicked();
	}
}

void View::handButtonClicked(int num) {
	if (hand_images[num].get_pixbuf()!=deck.null()) {
		controller_->handButtonClicked(hand[num]);
	}
}

void View::setToEmpty(Gtk::Image* images) {
	for (int i=0; i<13; i++) {
		images[i].set(deck.null());
	}
}

void View::updatePlayerStatsLabels() {
	for (int i=0; i<4; i++) {
		player_stats[i].set_label(std::to_string(points[i])+" points\n"+std::to_string(discards[i])+" discards");
	}
}

void View::updateAllCards(int current_player) {
	hand=model_->getHand(current_player);
	clubs=model_->getTableCardsBySuit(CLUB);
	diamonds=model_->getTableCardsBySuit(DIAMOND);
	hearts=model_->getTableCardsBySuit(HEART);
	spades=model_->getTableCardsBySuit(SPADE);
	legal=model_->getLegalPlays();
	cardVectorToImages(hand_images, hand, true);
	cardVectorToImages(club_images, clubs);
	cardVectorToImages(diamond_images, diamonds);
	cardVectorToImages(heart_images, hearts);
	cardVectorToImages(spade_images, spades);
	cardVectorToImages(legal_images, legal, true);
}

void View::clearHand() {
	hand.clear();
	setToEmpty(hand_images);
}

void View::clearLegal() {
	legal.clear();
	setToEmpty(legal_images);
}

void View::clearTable() {
	clubs.clear();
	diamonds.clear();
	hearts.clear();
	spades.clear();
	setToEmpty(club_images);
	setToEmpty(diamond_images);
	setToEmpty(heart_images);
	setToEmpty(spade_images);
}

void View::resetPlayerButtons() {
	for (int i=0; i<4; i++) {
		this->player_buttons[i].set_label("Human");
		this->player_buttons[i].set_sensitive(true);
		human[i]="h";
	}
}

void View::resetDiscardsAndPoints() {
	for (int i=0; i<4; i++) {
		discards[i]=0;
		points[i]=0;
	}
	updatePlayerStatsLabels();
}

void View::setPlayedCards(std::string played) {
	played_cards_panel.set_label(played);
	played_cards_panel.set_alignment(0,0);
}