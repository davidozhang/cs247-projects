/*
 *  MyDialogBox.h
 *  
 * Creates a dialog box that holds a radio button group with each radio button associated with a colour.
 * Outputs the colour chosen by the user.
 *
 *  Created by Caroline Kierstead on 28/05/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */
#ifndef __DIALOG_H
#define __DIALOG_H
#include <gtkmm.h>
#include <string>
using std::string;

class Dialog : Gtk::MessageDialog {
public:
	// Specifies the parent window of the dialog box and the title of the dialog box.
	Dialog( Gtk::Window & parentWindow, string message);
	virtual ~Dialog();
	
private:
};
#endif
