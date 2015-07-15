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


#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
#include <vector>
#include <string>
#include <map>
#include "DeckGUI.h"
#include "models/Card.h"
#include "observer.h"

class Controller;
class ModelFacade;


class View : public Gtk::Window, public Observer {
public:
	View( Controller*, ModelFacade* );
	virtual ~View();
	virtual void update(std::string);	// Observer Pattern: concrete update() method

private:
	// Observer Pattern: to access Model accessors without having to downcast subject
	ModelFacade *model_;
	
	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;

	// Card Images
	DeckGUI deck;

	std::vector<Card> clubs;
	std::vector<Card> diamonds;
	std::vector<Card> hearts;
	std::vector<Card> spades;
	std::vector<Card> hand;

	// Member widgets:
	Gtk::VBox main_box;
	Gtk::HBox top_panel;
	Gtk::Label cards_panel_label;
	Gtk::VBox cards_panel;
	Gtk::HBox clubs_on_table;
	Gtk::HBox diamonds_on_table;
	Gtk::HBox hearts_on_table;
	Gtk::HBox spades_on_table;
	Gtk::HBox players_panel_labels;
	Gtk::Label player_panel_label [4];
	Gtk::HBox players_panel;
	Gtk::VBox players [4];
	Gtk::Label player_hand_panel_label;
	Gtk::HBox player_hand_panel;
	Gtk::Entry text_field;
	Gtk::Button start_button;
	Gtk::Button end_button;
	Gtk::Button player_buttons[4];
	Gtk::Label player_stats[4];
	Gtk::Image club_images [13];
	Gtk::Image diamond_images [13];
	Gtk::Image heart_images [13];
	Gtk::Image spade_images [13];
	Gtk::Image hand_images [13];
	Gtk::Button hand_buttons [13];

	std::vector<std::string> human;

	// Signal handlers:
	void startButtonClicked();
	void endButtonClicked();
	void setActivePlayerButton(int);
	void cardVectorToImages(Gtk::Image*, std::vector<Card>, bool hand=false);
	void setToEmpty(Gtk::Image*);
	void playerButtonClicked(int);
	void handButtonClicked(int);

}; // View

#endif
