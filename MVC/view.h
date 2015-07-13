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
#include "DeckGUI.h"
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

	// Member widgets:
	Gtk::VBox main_box;
	Gtk::HBox top_panel;
	Gtk::Label cards_panel_label;
	Gtk::VBox cards_panel;
	Gtk::HBox clubs;
	Gtk::HBox diamonds;
	Gtk::HBox hearts;
	Gtk::HBox spades;
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
	Gtk::Image cards [52];
	Gtk::Image hand [13];
	Gtk::Button hand_buttons [13];

	bool human [4];

	// Signal handlers:
	void startButtonClicked();
	void endButtonClicked();
	void playerButtonClicked(int);

}; // View

#endif
