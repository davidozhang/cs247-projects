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
#include "model.h"
#include "subject.h"
#include "DeckGUI.h"
#include "dialog.h"
#include <iostream>
#include <string>

// Creates buttons with labels. Sets butBox elements to have the same size, 
// with 10 pixels between widgets
View::View(Controller *c, Model *m) : model_(m), controller_(c), main_box(false, 10), clubs(true, 5), diamonds(true, 5), hearts(true, 5), spades(true, 5), top_panel(false, 10), cards_panel(false, 10), players_panel(false, 10), player_hand_panel(false, 10){

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
	top_panel.add(text_field);
	end_button.set_label("End current game");
	top_panel.add(end_button);

	for (int i=0; i<52; i++) {
		cards[i].set(deck.null());
	}

	for (int i=0; i<13; i++) {
		clubs.add(cards[i]);
		diamonds.add(cards[i+13]);
		hearts.add(cards[i+26]);
		spades.add(cards[i+39]);
	}

	cards_panel.add(clubs);
	cards_panel.add(diamonds);
	cards_panel.add(hearts);
	cards_panel.add(spades);

	for (int i=0; i<4; i++) {
		player_panel_label[i].set_label("Player "+std::to_string(i+1));
		players_panel_labels.add(player_panel_label[i]);
	}
	for (int i=0; i<4; i++) {
		player_buttons[i].signal_clicked().connect( sigc::bind<int>(sigc::mem_fun(*this, &View::playerButtonClicked), i));
	}
	for (int i=0; i<4; i++) {
		player_buttons[i].set_label("Human");
		player_stats[i].set_label("0 points\n0 discards");
		players[i].add(player_buttons[i]);
		players[i].add(player_stats[i]);
		players_panel.add(players[i]);
	}

	for (int i=0; i<13; i++) {
		hand[i].set(deck.null());
		hand_buttons[i].set_image(hand[i]);
		player_hand_panel.add(hand_buttons[i]);
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


void View::update() {
  Suits suit = model_->suit();
  Faces face = model_->face();
  if ( suit == NOSUIT ) 
    cards[0].set( deck.null() );
  else
    cards[1].set( deck.image(face, suit) );
}

void View::startButtonClicked() {
	for (int i=0; i<4; i++) {
		this->player_buttons[i].set_label("Rage!");
	}
	//get initial player number here
	Dialog dialog(*this, "A new round begins. It's player 0's turn to play.");
}

void View::endButtonClicked() {
	for (int i=0; i<4; i++) {
		this->player_buttons[i].set_label("Human");
		human[i]=true;
	}
}

void View::playerButtonClicked(int num) {
	if (this->player_buttons[num].get_label()=="Human") {
		this->player_buttons[num].set_label("Computer");
		human[num]=false;
	} else if (this->player_buttons[num].get_label()=="Computer") {
		this->player_buttons[num].set_label("Human");
		human[num]=true;
	} else if (this->player_buttons[num].get_label()=="Rage") {

	}
}
