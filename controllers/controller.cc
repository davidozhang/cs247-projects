/*
 * MVC example of GTKmm program
 *
 * Controller class.  Is responsible for translating UI events (from the View)
 * into method calls to the Model.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#include "controller.h"
#include "../models/model_facade.h"

class ModelFacade;

Controller::Controller(ModelFacade *m) : model_(m) {}


void Controller::startButtonClicked(int seed, std::vector<std::string> human) {
	if (!model_->getGameState()) {
		for (int i=0; i<4; i++) {
			model_->setPlayerType(i, human[i]);
		}
	}
	model_->startGame(seed);
}


void Controller::endButtonClicked() {
	model_->endGame();
}

void Controller::rageButtonClicked() {
	model_->rageQuit();
}

void Controller::handButtonClicked(Card card) {
	model_->selectCard(card);
}