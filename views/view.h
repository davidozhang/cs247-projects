#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
#include <vector>
#include <string>
#include <map>
#include "DeckGUI.h"
#include "../models/Card.h"
#include "../observer.h"

class Controller;
class ModelFacade;


class View : public Gtk::Window, public Observer {
public:
	View( Controller*, ModelFacade* );
	virtual ~View();
	virtual void update(std::string);
private:
	ModelFacade *model_;
	Controller *controller_;
	DeckGUI deck;

	std::vector<Card> clubs;
	std::vector<Card> diamonds;
	std::vector<Card> hearts;
	std::vector<Card> spades;
	std::vector<Card> hand;
	std::vector<Card> legal;
	std::vector<std::string> human;
	int discards [4];
	int points [4];

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
	Gtk::Label played_cards_panel;
	Gtk::Label legal_panel_label;
	Gtk::HBox legal_panel;
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
	Gtk::Image legal_images [13];
	Gtk::Button hand_buttons [13];

	void startButtonClicked();
	void endButtonClicked();
	void setActivePlayerButton(int);
	void cardVectorToImages(Gtk::Image*, std::vector<Card>, bool hand=false);
	void setToEmpty(Gtk::Image*);
	void setPlayedCards(std::string);
	void updatePlayerStatsLabels();
	void updateAllCards(int);
	void clearTable();
	void clearHand();
	void clearLegal();
	void resetPlayerButtons();
	void resetDiscardsAndPoints();
	void playerButtonClicked(int);
	void handButtonClicked(int);
}; // View

#endif
