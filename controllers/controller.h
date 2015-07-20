#ifndef MVC_CONTROLLER_H
#define MVC_CONTROLLER_H


#include <gtkmm.h>
#include <vector>
#include <string>
#include "../models/model_facade.h"

class ModelFacade;

class Controller {
public:
   Controller(ModelFacade*);
   void startButtonClicked(int, std::vector<std::string>);	// check the game state, if game is not on, set the player type, then start the game
   void endButtonClicked();									// call endGame() in model
   void rageButtonClicked();								// call rageQuit() in model
   void handButtonClicked(Card);							// call selectCard(Card) in model
private:
   ModelFacade *model_;
}; // Controller


#endif

