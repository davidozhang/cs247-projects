/*
 * MVC example of GTKmm program
 *
 * View class.  Is responsible for buttons (that user clicks) and for displaying
 * the top card of the deck.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#include "observer.h"
#include "view.h"
#include "controller.h"
#include "models/model_facade.h"
#include "subject.h"
#include "DeckGUI.h"
#include "dialog.h"
#include <iostream>
#include <string>

// Creates buttons with labels. Sets butBox elements to have the same size, 
// with 10 pixels between widgets
View::View(Controller *c, ModelFacade *m) : model_(m), controller_(c), main_box(false, 10), clubs_on_table(true, 5), diamonds_on_table(true, 5), hearts_on_table(true, 5), spades_on_table(true, 5), top_panel(false, 10), cards_panel(false, 10), players_panel(false, 10), player_hand_panel(false, 10){

	// Sets some properties of the window.
	set_title( "Straights UI - David & Jerry" );
	set_border_width( 10 );
	
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
		clubs_on_table.add(club_images[i]);
		diamonds_on_table.add(diamond_images[i]);
		hearts_on_table.add(heart_images[i]);
		spades_on_table.add(spade_images[i]);
	}
	cards_panel.add(clubs_on_table);
	cards_panel.add(diamonds_on_table);
	cards_panel.add(hearts_on_table);
	cards_panel.add(spades_on_table);

	for (int i=0; i<4; i++) {
		player_panel_label[i].set_label("Player "+std::to_string(i+1));
		players_panel_labels.add(player_panel_label[i]);
	}
	for (int i=0; i<4; i++) {
		player_buttons[i].signal_clicked().connect( sigc::bind<int>(sigc::mem_fun(*this, &View::playerButtonClicked), i));
	}
	for (int i=0; i<4; i++) {
		points[i]=0;
		discards[i]=0;
		player_buttons[i].set_label("Human");
		player_stats[i].set_label(std::to_string(points[i])+" points\n"+std::to_string(discards[i])+" discards");
		players[i].add(player_buttons[i]);
		players[i].add(player_stats[i]);
		players_panel.add(players[i]);
	}
	for (int i=0; i<13; i++) {
		hand_buttons[i].signal_clicked().connect( sigc::bind<int>(sigc::mem_fun(*this, &View::handButtonClicked), i));
	}
	for (int i=0; i<13; i++) {
		hand_buttons[i].set_image(hand_images[i]);
		player_hand_panel.add(hand_buttons[i]);
	}

	for (int i=0; i<4; i++) {
		human.push_back("h");
	}

	// Associate button "clicked" events with local onButtonClicked() method defined below.
	start_button.signal_clicked().connect( sigc::mem_fun( *this, &View::startButtonClicked ) );
	end_button.signal_clicked().connect( sigc::mem_fun( *this, &View::endButtonClicked ) );
	
	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

} // View::View

View::~View() {}


void View::update(std::string state) {
  /**Suits suit = model_->suit();
  Faces face = model_->face();
  if ( suit == NOSUIT ) 
	cards[0].set( deck.null() );
  else
	cards[1].set( deck.image(face, suit) );**/
	int current_player = model_->getCurrentPlayer();
	if (state=="new round") {
		Dialog dialog(*this, "A new round begins. It's player "+std::to_string(current_player+1)+"'s turn to play.");
		setActivePlayerButton(current_player);
		hand=model_->getHand(current_player);
		clubs=model_->getTableCardsBySuit(CLUB);
		diamonds=model_->getTableCardsBySuit(DIAMOND);
		hearts=model_->getTableCardsBySuit(HEART);
		spades=model_->getTableCardsBySuit(SPADE);
		cardVectorToImages(hand_images, hand, true);
		cardVectorToImages(club_images, clubs);
		cardVectorToImages(diamond_images, diamonds);
		cardVectorToImages(heart_images, hearts);
		cardVectorToImages(spade_images, spades);
	} else if (state=="end round") {
		Dialog dialog(*this, model_->getRoundEndResult());
	} else if (state=="new turn") {
		setActivePlayerButton(current_player);
		hand=model_->getHand(current_player);
		clubs=model_->getTableCardsBySuit(CLUB);
		diamonds=model_->getTableCardsBySuit(DIAMOND);
		hearts=model_->getTableCardsBySuit(HEART);
		spades=model_->getTableCardsBySuit(SPADE);
		for (int i=0; i<4; i++) {
			discards[i]=model_->getDiscards(i);
		}
		for (int i=0; i<4; i++) {
			player_stats[i].set_label(std::to_string(points[i])+" points\n"+std::to_string(discards[i])+" discards");
		}
		cardVectorToImages(hand_images, hand, true);
		cardVectorToImages(club_images, clubs);
		cardVectorToImages(diamond_images, diamonds);
		cardVectorToImages(heart_images, hearts);
		cardVectorToImages(spade_images, spades);
	} else if (state=="end game") {
		hand.clear();
		setToEmpty(hand_images);
		clubs.clear();
		diamonds.clear();
		hearts.clear();
		spades.clear();
		setToEmpty(club_images);
		setToEmpty(diamond_images);
		setToEmpty(heart_images);
		setToEmpty(spade_images);
	} else if (state=="invalid play") {
		Dialog dialog(*this, "Invalid Move, There are still legal moves.");
	} else if (state=="has winner") {
		std::vector<int> winners;
		model_->getWinners(winners);
		for (int i=0; i<winners.size(); i++) {
			Dialog dialog(*this, "Player "+ std::to_string(winners[i]+1) +" wins!");
		}
	} else {
		//invalid state
	}
}

void View::cardVectorToImages(Gtk::Image* images, std::vector<Card> cards, bool hand) {
	for (int i=0; i<cards.size(); i++) {
		if (hand) {
			images[i].set(deck.image(cards[i].getRank(), cards[i].getSuit()));
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
	for (int i=0; i<4; i++) {
		this->player_buttons[i].set_label("Human");
		this->player_buttons[i].set_sensitive(true);
		human[i]="h";
	}
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
	} else if (this->player_buttons[num].get_label()=="Rage") {
		controller_->rageButtonClicked();
	}
}

void View::handButtonClicked(int num) {
	if (num<hand.size()) {
		controller_->handButtonClicked(hand[num]);
	}
}

void View::setToEmpty(Gtk::Image* images) {
	for (int i=0; i<13; i++) {
		images[i].set(deck.null());
	}
}