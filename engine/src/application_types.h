#pragma once

#include "core/engine.h"
#include "platform/platform.h"

struct render_packet;
struct frame_data;

// Represents the various stages of application lifecycle
typedef enum application_stage {
	APPLICATION_STAGE_UNINITIALIZED,
	APPLICATION_STAGE_BOOTING,
	APPLICATION_STAGE_BOOT_COMPLETE,
	APPLICATION_STAGE_INITIALIZING,
	APPLICATION_STAGE_INITIALIZED,
	APPLICATION_STAGE_RUNNING,
	APPLICATION_STAGE_SHUTTING_DOWN
} application_stage;

/**
 * Represents the basic game state in a game
 * Called for creation by the application
 */
typedef struct application {
    // The application configuration
    application_config app_config;
    
    // Function pointer to the application's boot sequence. This should
    // fill out the application config with the application's specific requirements.
    b8 (*boot)(struct application* app_inst);

    // Function pointer to application's initialize function
    b8 (*initialize)(struct application* app_inst);

    // Function pointer to application's update function
    b8 (*update)(struct application* app_inst, struct frame_data* p_frame_data);
    
    b8 (*prepare_render_packet)(struct application* app_inst, struct render_packet* packet, struct frame_data* p_frame_data);
    // Function pointer to application's render function
    b8 (*render)(struct application* app_inst, struct render_packet* packet, struct frame_data* p_frame_data);

    // Funtion pointer to handle resizes, if applicable
    void (*on_resize)(struct application* app_inst, u32 width, u32 height);

	// Shuts down the application, prompting release of resources
	void (*shutdown)(struct application* app_inst);
	
	void (*lib_on_unload)(struct application* game_inst);

	void (*lib_on_load)(struct application* game_inst);
	
	// The application stage of execution
	application_stage stage;

    // Game-specific game state. Created and managed by the game
    void* state;

    // Engine state
    void* engine_state;
    
    // TODO: Move this to somewhere better...
    dynamic_library renderer_library;
    renderer_plugin render_plugin;
    
	dynamic_library game_library;
} application;
