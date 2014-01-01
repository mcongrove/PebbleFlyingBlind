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
		VIBRATE = persist_read_int(KEY_VIBRATE);
	}
	
	APP_LOG(APP_LOG_LEVEL_INFO, "SELECTED VIBRATE: %d", VIBRATE);
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
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	
	int tHour = 5;
	int tMin = 0;
	
	uint32_t segments[25];
	segments[0] = 100;
	
	if (tMin == 0) {
		if (tHour == 1) {
				static const uint32_t const segments1[] = { 500, 100, 100 };
				VibePattern pat = { .durations = segments1, .num_segments = ARRAY_LENGTH(segments1) };
		} else if (tHour == 2) {
				static const uint32_t const segments2[] = { 500, 100, 100, 100, 100 };
				VibePattern pat = { .durations = segments2, .num_segments = ARRAY_LENGTH(segments2) };
		} else if (tHour == 3) {
				static const uint32_t const segments3[] = { 500, 100, 100, 100, 100, 100, 100 };
				VibePattern pat = { .durations = segments3, .num_segments = ARRAY_LENGTH(segments3) };
		} else if (tHour == 4) {
				static const uint32_t const segments4[] = { 500, 100, 100, 100, 100, 100, 100, 100, 100 };
				VibePattern pat = { .durations = segments4, .num_segments = ARRAY_LENGTH(segments4) };
		} else if (tHour == 5) {
				static const uint32_t const segments5[] = { 500, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
				VibePattern pat = { .durations = segments5, .num_segments = ARRAY_LENGTH(segments5) };
		} else if (tHour == 6) {
				static const uint32_t const segments6[] = { 500, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
				VibePattern pat = { .durations = segments6, .num_segments = ARRAY_LENGTH(segments6) };
		} else if (tHour == 7) {
				static const uint32_t const segments7[] = { 500, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
				VibePattern pat = { .durations = segments7, .num_segments = ARRAY_LENGTH(segments7) };
		} else if (tHour == 8) {
				static const uint32_t const segments8[] = { 500, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
				VibePattern pat = { .durations = segments8, .num_segments = ARRAY_LENGTH(segments8) };
		} else if (tHour == 9) {
				static const uint32_t const segments9[] = { 500, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
				VibePattern pat = { .durations = segments9, .num_segments = ARRAY_LENGTH(segments9) };
		} else if (tHour == 10) {
				static const uint32_t const segments10[] = { 500, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
				VibePattern pat = { .durations = segments10, .num_segments = ARRAY_LENGTH(segments10) };
		} else if (tHour == 11) {
				static const uint32_t const segments11[] = { 500, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
				VibePattern pat = { .durations = segments11, .num_segments = ARRAY_LENGTH(segments11) };
		} else if (tHour == 12) {
				static const uint32_t const segments12[] = { 500, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
				VibePattern pat = { .durations = segments12, .num_segments = ARRAY_LENGTH(segments12) };
		}
	}
	
	if ((VIBRATE == 1 && tMin == 30) || (VIBRATE == 2 && (tMin == 15 || tMin == 30 || tMin == 45))) {
		if (tMin == 15) {
			static const uint32_t const segments15[] = { 100 };
		}
		
		if (tMin == 30) {
			static const uint32_t const segments30[] = { 100, 100, 100 };
		}
		
		if (tMin == 45) {
			static const uint32_t const segments45[] = { 100, 100, 100, 100, 100, 100 };
		}
	}
	
	VibePattern pat = { .durations = segments, .num_segments = ARRAY_LENGTH(segments) };
	
	vibes_enqueue_custom_pattern(pat);
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