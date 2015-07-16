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
   void startButtonClicked(int, std::vector<std::string>);
   void endButtonClicked();
   void rageButtonClicked();
   void handButtonClicked(Card);
private:
   ModelFacade *model_;
}; // Controller


#endif

