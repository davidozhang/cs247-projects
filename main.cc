#include <gtkmm/main.h>
#include "models/model_facade.h"
#include "controllers/controller.h"
#include "views/view.h"

int main( int argc, char * argv[] ) {
	Gtk::Main  kit( argc, argv );         // Initialize gtkmm with the command line arguments, as appropriate.
	ModelFacade model;                          // Create model
        Controller controller( &model );  // Create controller
	View view( &controller, &model );     // Create the view -- is passed handle to controller and model
	Gtk::Main::run( view );               // Show the window and return when it is closed.
	
	return 0;
} // main
