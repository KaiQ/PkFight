#include "Menu.h"

uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return NUM_MENU_SECTIONS;
}

uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  switch (section_index) {
    case MENU_SECTION_MAIN:
      return NUM_FIRST_MENU_ITEMS;
    case MENU_SECTION_ATTACK:
      return 4; //Monster count TODO: DEFINE
    default:
      return 0;
  }
}

int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return 0;
}

void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  // Determine which section we're working with
  return;
  switch (section_index) {
    case 0:
      // Draw title text in the section header
      menu_cell_basic_header_draw(ctx, cell_layer, "Some example items");
      break;
    case 1:
      menu_cell_basic_header_draw(ctx, cell_layer, "One more");
      break;
  }
}

void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  menu_cell_title_draw(ctx, cell_layer, active_field[cell_index->row]);
  return;
  // Determine which section we're going to draw in
  //switch (cell_index->section) {
  //  case 0:
  //    // Use the row to specify which item we'll draw
  //    switch (cell_index->row) {
  //      case 0:
  //        // This is a basic menu item with a title and subtitle
  //        menu_cell_title_draw(ctx, cell_layer, active_field[0]);
  //        break;
  //      case 1:
  //        // This is a basic menu icon with a cycling icon
  //        menu_cell_title_draw(ctx, cell_layer, active_field[1]);
  //        break;
  //      case 2:
  //        {
  //          // Here we use the graphics context to draw something different
  //          // In this case, we show a strip of a watchface's background
  //          GSize size = layer_get_frame(cell_layer).size;
  //          //graphics_draw_bitmap_in_rect(ctx, s_background_bitmap, GRect(0, 0, size.w, size.h));
  //        }
  //        break;
  //    }
  //    break;
  //  case 1:
  //    switch (cell_index->row) {
  //      case 0:
  //        // There is title draw for something more simple than a basic menu item
  //        menu_cell_title_draw(ctx, cell_layer, "Final Item");
  //        break;
  //    }
  //}
}

void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  switch (cell_index->section)
  {
    case MENU_SECTION_MAIN:
      {
        switch (cell_index->row) {
          case MENU_ROW_MAIN_ATTACK:
            {
              for (int i = 0; i < 4; i++)
                menu_attacks[i] = monster_get_attack_name((Monster*)data, i);
              active_field = menu_attacks;
              menu_layer_reload_data(menu_layer);
              menu_layer_set_selected_index(menu_layer,
                  (MenuIndex) { .section = MENU_SECTION_ATTACK, .row = 0 },
                  MenuRowAlignTop,
                  false);
              layer_mark_dirty(menu_layer_get_layer(menu_layer));
              break;
            }
        }
      }
  }
}

