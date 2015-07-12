/*
 *  MyDialogBox.cc
 *
 *  Created by Caroline Kierstead on 28/05/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */
#include "dialog.h"
#include <gtkmm/stock.h>
#include <iostream>

// Specifies the parent window of the dialog box and the title of the dialog box.
Dialog::Dialog( Gtk::Window & parentWindow, string message) : Gtk::MessageDialog( parentWindow, message) {

	// Add a standard "ok" buttons with the appropriate responses when clicked.
	show_all_children();

    // Wait for a response from the dialog box.
	int result = run();
    switch (result) {
        case Gtk::RESPONSE_OK:
            /**for ( int i = 0; i < messages.size(); i++ ) {
				if ( buttons[i]->get_active() ) {
					std::cout << "chose '" << messages[i] << "'" << std::endl;
					break;
				} // if
			} // for**/
            break;
    }  	
}

Dialog::~Dialog() {
}
