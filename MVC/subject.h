/*
 * MVC example of GTKmm program
 *
 * Subject class.  Abstract class for Observer Pattern
 *
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#ifndef MVC_SUBJECT_H
#define MVC_SUBJECT_H

#include <set>
#include <string>

class Observer;

class Subject {
public:
       void subscribe( Observer* );
       void unsubscribe( Observer* );

protected:
       void notify();
       std::string state_;
       /*
		new round
                     output "A new round has begin, its " model->getCurrentPlayer()+1 " 's turn"
                     update points for all players
                     update discards for all players (to 0)
		end round
                     output getRoundResult()
		new turn
                     update hand
                     update discards for all players
                     update cards on the table
                     update who is current player (ie the rage button)
		end game
                     update hand (to become empty)
                     update table (to become empty)
                     update rage buttons (to become h/c)
		invalid play
                     message dialogue: the player has selected a card not in legal play, and there are some legal plays
              has winner
                     initialize an empty vector<int>, call getWinners(vector), then iterate this vector to output message dialogue
       */
private:
       typedef std::set< Observer* > Observers;
       Observers observers_;
}; // Subject


#endif
