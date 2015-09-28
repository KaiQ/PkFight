#include "Menu.h"

uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return NUM_MENU_SECTIONS;
}

int16_t menu_get_cell_height_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
  return MENU_HEIGHT;
}

uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  switch (active_section) {
    case MENU_SECTION_MAIN:
      return NUM_FIRST_MENU_ITEMS;
    case MENU_SECTION_ATTACK:
      return 4 + 1; //Monster count + EXIT TODO: DEFINE
    default:
      return 0;
  }
}

int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return 0;
}

void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  // Determine which section we're working with
  switch (section_index) {
    case MENU_SECTION_MAIN:
      // Draw title text in the section header
      menu_cell_basic_header_draw(ctx, cell_layer, "Main Section");
      break;
    case MENU_SECTION_ATTACK:
      menu_cell_basic_header_draw(ctx, cell_layer, "Attack Section");
      break;
  }
}


uint8_t last_item_index(uint8_t section)
{
  switch(section)
  {
    case MENU_SECTION_MAIN:
      return NUM_FIRST_MENU_ITEMS;
    case MENU_SECTION_ATTACK:
      return 4;
  }
  return 0;
}


void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  switch(active_section)
  {
    case MENU_SECTION_MAIN:
      {
        if (cell_index->row >= last_item_index(MENU_SECTION_MAIN))
        {
          menu_cell_title_draw(ctx, cell_layer, EXIT_TEXT);
          return;
        }
        menu_cell_title_draw(ctx, cell_layer, menu_main_items[cell_index->row]);
        return;
      }
    case MENU_SECTION_ATTACK:
      {
        if (cell_index->row >= last_item_index(MENU_SECTION_ATTACK))
        {
          menu_cell_title_draw(ctx, cell_layer, EXIT_TEXT);
          return;
        }
        menu_cell_title_draw(ctx, cell_layer, monster_get_attack_name((Monster*)data, cell_index->row));
        return;
      }
  }
  return;
}


void set_menu_section(MenuLayer *menu_layer, uint8_t section, void *data)
{
  switch(section)
  {
    case MENU_SECTION_MAIN:
      {
        active_section = MENU_SECTION_MAIN;
        break;
      }
    case MENU_SECTION_ATTACK:
      {
        active_section = MENU_SECTION_ATTACK;
        break;
      }
  }
  menu_layer_reload_data(menu_layer);
  menu_layer_set_selected_index(menu_layer,
      (MenuIndex) { .section = 0, .row = 0 },
      MenuRowAlignTop,
      false);
  layer_mark_dirty(menu_layer_get_layer(menu_layer));
}

void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  switch (active_section)
  {
    case MENU_SECTION_MAIN:
      {
        switch (cell_index->row) {
          case MENU_ROW_MAIN_ATTACK:
            {
              set_menu_section(menu_layer, MENU_SECTION_ATTACK, data);
              break;
            }
          case MENU_ROW_MAIN_BAG:
            {
              break;
            }
          case MENU_ROW_MAIN_RUN:
            {
              updateStatus("We should Run...");
              break;
            }
        }
        break;
      }
    case MENU_SECTION_ATTACK:
      {
        if (cell_index->row >= last_item_index(MENU_SECTION_ATTACK))
        {
          set_menu_section(menu_layer, MENU_SECTION_MAIN, data);
          return;
        }
        player_attack((Monster*) data, monster_get_attack((Monster*) data, cell_index->row));
        static char temp[90]; //just some large field
        strncpy(temp, "dein Monster benutzt ", 90);
        strcat(temp, monster_get_attack_name((Monster*)data, cell_index->row));
        updateStatus(temp);
        set_menu_section(menu_layer, MENU_SECTION_MAIN, data);
        break;
      }
    case MENU_SECTION_BAG:
      {
        updateStatus("Lets look in our Bag");
        break;
      }
  }
}

