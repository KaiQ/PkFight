#include <pebble.h>
#include "Monster.h"
#include "Resolution.h"
#include "Menu.h"

static Window *window;
static TextLayer *text_layer;
static MenuLayer *s_menu_layer;
static BitmapLayer *s_icon_layer;
static BitmapLayer *s_icon_layer2;
static GBitmap *s_monster_one, *s_monster_two;
static uint32_t monster_ids[5] = {RESOURCE_ID_MONSTER_ONE, RESOURCE_ID_MONSTER_TWO, RESOURCE_ID_MONSTER_THREE, RESOURCE_ID_MONSTER_FOUR, RESOURCE_ID_MONSTER_FIVE };

void setup_menu_items();
void setup_menu_sections();

static void menu_handler_attack (int index, void *context) {
  text_layer_set_text(text_layer, s_monster1->name);
  monster_attack(s_monster2, s_monster1);
  monster_attack(s_monster1, s_monster2);
  Layer *window_layer = window_get_root_layer(window);
  layer_mark_dirty(window_layer);
}

static void menu_handler_bag (int index, void *context) {
  text_layer_set_text(text_layer, "Lets look in our bag!");
}

static void menu_handler_monster (int index, void *context) {
  text_layer_set_text(text_layer, "Monster Change");
}

static void menu_handler_run (int index, void *context) {
  text_layer_set_text(text_layer, "RUN AWAY!!!");
}


static void click_config_provider(void *context) {
  //window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  //window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  //window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  //graphics_context_set_fill_color(ctx, GColorFromRGB(0, 255, 0));
  uint8_t life1 = monster_get_life_percent(s_monster1, LIFE_WIDTH);
  uint8_t life2 = monster_get_life_percent(s_monster2, LIFE_WIDTH);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, GRect(bounds.size.w - LIFE_WIDTH_MARGIN - LIFE_WIDTH, bounds.size.h - LIFE_OWN_MARGIN, LIFE_WIDTH, LIFE_HEIGHT), 0, GCornerNone);
  graphics_fill_rect(ctx, GRect(LIFE_WIDTH_MARGIN, LIFE_ENEMY_MARGIN, LIFE_WIDTH, LIFE_HEIGHT), 0, GCornerNone);
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(bounds.size.w - LIFE_WIDTH_MARGIN - LIFE_WIDTH, bounds.size.h - LIFE_OWN_MARGIN, life1, LIFE_HEIGHT), 0, GCornerNone);
  graphics_fill_rect(ctx, GRect(LIFE_WIDTH_MARGIN, LIFE_ENEMY_MARGIN, life2, LIFE_HEIGHT), 0, GCornerNone);
}


GBitmap* getRandomMonster()
{
  return gbitmap_create_with_resource(monster_ids[rand() % 5]);
}


static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_menu_layer = menu_layer_create((GRect)
      {
      .origin = { 0, bounds.size.h - MENU_HEIGHT },
      .size = { bounds.size.w, MENU_HEIGHT }
      });

  menu_layer_set_callbacks(s_menu_layer, s_monster1, (MenuLayerCallbacks){
      .get_num_sections = menu_get_num_sections_callback,
      .get_num_rows = menu_get_num_rows_callback,
      .get_header_height = menu_get_header_height_callback,
      .draw_header = menu_draw_header_callback,
      .draw_row = menu_draw_row_callback,
      .select_click = menu_select_callback,
      });

  menu_layer_set_click_config_onto_window(s_menu_layer, window);
  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));

  s_monster_one = getRandomMonster();
  s_icon_layer = bitmap_layer_create((GRect)
      {
      .origin = { MARGIN, bounds.size.h - MONSTER_OWN_MARGIN },
      .size = { MONSTER_WIDTH, MONSTER_HEIGHT}
      });
  bitmap_layer_set_bitmap(s_icon_layer, s_monster_one);
  bitmap_layer_set_compositing_mode(s_icon_layer, GCompOpSet);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_icon_layer));

  s_monster_two = getRandomMonster();
  s_icon_layer2 = bitmap_layer_create((GRect)
      {
      .origin = { bounds.size.w - MARGIN - MONSTER_WIDTH, MARGIN },
      .size = { MONSTER_WIDTH, MONSTER_HEIGHT}
      });
  bitmap_layer_set_bitmap(s_icon_layer2, s_monster_two);
  bitmap_layer_set_compositing_mode(s_icon_layer2, GCompOpSet);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_icon_layer2));


  text_layer = text_layer_create((GRect)
      {
      .origin = { 0, bounds.size.h - STATUS_MARGIN},
      .size = { bounds.size.w, STATUS_HEIGHT }
      });
  text_layer_set_text(text_layer, "");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
  layer_set_update_proc(window_layer, update_proc);
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}


static void init(void) {
  srand(time(NULL));
  window = window_create();

  s_monster1 = monster_create("Monster_own", 35);
  s_monster2 = monster_create("Monster_enemy", 64);

  //active_field = menu_items;

  window_set_background_color(window, GColorWhite);

  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload,
      });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
