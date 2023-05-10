#pragma once

#include "core/engine.h"
#include "core/logger.h"
#include "application_types.h"

// Externally-defined function to create an application
extern b8 create_application(application* out_app);

extern b8 initialize_application(application* app);

/**
 * The main entry point of the application 
 */
int main(void) {
    // Request the game instance from the application
    application app_inst = {0};
    if(!create_application(&app_inst)) {
        KFATAL("Could not create application!");
        return -1;
    }

    // Ensure the function pointers exist
    if(!app_inst.render || !app_inst.update || !app_inst.initialize || !app_inst.on_resize) {
        KFATAL("The application's function pointers must be assigned!");
        return -2;
    }

    // Initialization
    if(!engine_create(&app_inst)) {
        KFATAL("Engine failed to create!");
        return 1;
    }

	if(!initialize_application(&app_inst)) {
		KFATAL("Could not initialize application!");
		return -1;
	}
	
    // Begin the engine loop
    if(!engine_run(&app_inst)) {
        KINFO("Application did not shutdown gracefully.");
        return 2;
    }

    return 0;
}