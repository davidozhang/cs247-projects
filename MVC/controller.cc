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
#include "models/model_facade.h"

class ModelFacade;

Controller::Controller(ModelFacade *m) : model_(m) {}


void Controller::startButtonClicked() {
} 


void Controller::endButtonClicked() {
} 
