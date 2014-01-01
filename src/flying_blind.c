/**
 * This code is provided under the Apache 2.0 license.
 * Please read the LICENSE.md file for more information
 * 
 * Copyright (c) 2013 Matthew Congrove (http://github.com/mcongrove)
 */
#include <pebble.h>

static char THEME[6] = "dark";
static int VIBRATE = 0;

Window *window;
InverterLayer *inverter_layer;

enum {
	KEY_THEME,
	KEY_VIBRATE
};

static void set_theme() {
	if (persist_exists(KEY_THEME)) {
		persist_read_string(KEY_THEME, THEME, 7);
	}
	
	APP_LOG(APP_LOG_LEVEL_INFO, "SELECTED THEME: %s", THEME);
	
	bool hide = strcmp(THEME, "light") == 0 ? true : false;
	
	layer_set_hidden(inverter_layer_get_layer(inverter_layer), hide);
}

static void set_vibrate() {
	if (persist_exists(KEY_VIBRATE)) {
		TIME_DISPLAY = persist_read_int(KEY_VIBRATE);
	}
	
	APP_LOG(APP_LOG_LEVEL_INFO, "SELECTED VIBRATE: %d", TIME_DISPLAY);
}

static void in_received_handler(DictionaryIterator *iter, void *context) {
	Tuple *theme_tuple = dict_find(iter, KEY_THEME);
	Tuple *vibrate_tuple = dict_find(iter, KEY_VIBRATE);
	
	if (theme_tuple) {
		persist_write_string(KEY_THEME, theme_tuple->value->cstring);
		strncpy(THEME, theme_tuple->value->cstring, 6);
		
		set_theme();
	}
	
	if (vibrate_tuple) {
		int vibrate_data = vibrate_tuple->value->data[0];
		
		persist_write_int(KEY_VIBRATE, vibrate_data);
		VIBRATE = vibrate_data;
		
		set_vibrate();
	}
}

static void in_dropped_handler(AppMessageResult reason, void *context) {
	
}

static void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {
	time_t t = time(NULL);
	struct tm *now = localtime(&t);
	
	
}

static void init() {
	app_message_register_inbox_received(in_received_handler);
	app_message_register_inbox_dropped(in_dropped_handler);
	app_message_open(64, 0);
	
	window = window_create();
	window_set_background_color(window, GColorWhite);
	window_stack_push(window, true);
	
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);
	
	// Create the inverter layer
	inverter_layer = inverter_layer_create(bounds);
	layer_add_child(window_layer, inverter_layer_get_layer(inverter_layer));
	
	tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);
	
	set_theme();
	set_vibrate();
}

static void deinit() {
	window_destroy(window);
	inverter_layer_destroy(inverter_layer);
	
	tick_timer_service_unsubscribe();
	app_message_deregister_callbacks();
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}