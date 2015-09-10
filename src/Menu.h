#ifndef MENU_H
#define MENU_H

#include <pebble.h>
#include "Properties.h"
#include "Monster.h"

#define NUM_MENU_SECTIONS 0
#define NUM_MENU_ICONS 0
#define NUM_FIRST_MENU_ITEMS 4


static char *menu_items[NUM_FIRST_MENU_ITEMS]  = { "Angriff", "Rucksack", "Monster", "Fliehen" };
static char *menu_attacks[4] = { "1", "2", "3", "4" };
static char **active_field = menu_items;

uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data);
uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data);
int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data);
void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data);
void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data);
void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data);


#endif

