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
	View( Controller*, ModelFacade* );		//Constructor
	virtual ~View();						//Destructor
	virtual void update(std::string);		//Updates certain parts of the view when the model changes to conform with the Observer pattern
private:
	ModelFacade *model_;					//Pointer to the model facade
	Controller *controller_;				//Pointer to the controller
	DeckGUI deck;							//Reference the deck GUI images

	std::vector<Card> clubs;				//vector of club cards
	std::vector<Card> diamonds;				//vector of diamond cards
	std::vector<Card> hearts;				//vector of heart cards
	std::vector<Card> spades;				//vector of spade cards
	std::vector<Card> hand;					//vector of cards in player's hand
	std::vector<Card> legal;				//vector of all legal cards available for play; part of the bonus feature
	std::vector<std::string> human;			//vector to keep track of whether each player is human or computer
	int discards [4];						//array to keep track of each player's discards
	int points [4];							//array to keep track of each player's points

	Gtk::VBox main_box;						//VBox that contains everything else for the view
	Gtk::HBox top_panel;					//Contains the start, end game buttons and the text field
	Gtk::Label cards_panel_label;			//Label for the table
	Gtk::VBox cards_panel;					//VBox for the table
	Gtk::HBox clubs_on_table;				//Contains the images of all club cards
	Gtk::HBox diamonds_on_table;			//Contains the images of all diamond cards
	Gtk::HBox hearts_on_table;				//Contains the images of all heart cards
	Gtk::HBox spades_on_table;				//Contains the images of all spade cards
	Gtk::HBox players_panel_labels;			//Contains the labels for all player panels in the view
	Gtk::Label player_panel_label [4];		//Array of labels for Player 1...Player 4 in the view
	Gtk::HBox players_panel;				//Contains the panels for all 4 players
	Gtk::VBox players [4];					//Array that contains the Rage button and the stats for each player
	Gtk::Label player_hand_panel_label;		//Label for the player hand in the view
	Gtk::HBox player_hand_panel;			//Contains the card images on the player hand
	Gtk::Label played_cards_panel;			//Contains the text for all played cards by the player
	Gtk::Label legal_panel_label;			//Label for the legal moves panel
	Gtk::HBox legal_panel;					//Contains the card images of all legal moves
	Gtk::Entry text_field;					//Text field for seed value input; defaults to 0
	Gtk::Button start_button;				//Start game button
	Gtk::Button end_button;					//End game button
	Gtk::Button player_buttons[4];			//Array of buttons for each player to rage and select human/computer
	Gtk::Label player_stats[4];				//Array of the player stats labels for each player
	Gtk::Image club_images [13];			//Array of images of club cards
	Gtk::Image diamond_images [13];			//Array of images of diamond cards
	Gtk::Image heart_images [13];			//Array of images of heart cards
	Gtk::Image spade_images [13];			//Array of images of spade cards
	Gtk::Image hand_images [13];			//Array of images of cards on player's hand
	Gtk::Image legal_images [13];			//Array of images of cards that are legal moves
	Gtk::Button hand_buttons [13];			//Array of buttons for selecting card on player's hand

	void startButtonClicked();				//linked to controller when the start game button is clicked
	void endButtonClicked();				//linked to controller when the end game button is clicked
	void setActivePlayerButton(int);		//sets the rage button to be active when a player is active
	void cardVectorToImages(Gtk::Image*, std::vector<Card>, bool hand=false);		//Converts the information from a Card vector into images for the view
	void setToEmpty(Gtk::Image*);			//Sets an array of Gtk::Images to the empty card images
	void setPlayedCards(std::string);		//Sets the text to be displayed for played cards by each player
	void updatePlayerStatsLabels();			//Updates all player stats labels
	void updateAllCards(int);				//Update all card arrays and their associated card image arrays
	void clearTable();						//Sets the card images on the table to empty card images
	void clearHand();						//Sets the card images on the player's hand to empty card images
	void clearLegal();						//Sets the cards images for legal moves to empty card images
	void resetPlayerButtons();				//Resets all player buttons to Human/Computer choice
	void resetDiscardsAndPoints();			//Resets the discard and point information for all players
	void playerButtonClicked(int);			//linked to controller when a player's human/computer or rage button is clicked
	void handButtonClicked(int);			//linked to controller when a card is selected from the player's hand
}; // View

#endif
