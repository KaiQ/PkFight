#include <pebble.h>

static Window *window;
static TextLayer *text_layer;
static SimpleMenuLayer * s_simple_menu_layer;
static SimpleMenuItem s_menu_items[4];
static SimpleMenuSection s_menu_sections[1];
static char *s_menu_items_names[4] = {"Attack", "Bag", "Monster",  "Run"};

void setup_menu_items();
void setup_menu_sections();

void setup_menu_items()
{
  for (int i = 0; i < (int)(sizeof(s_menu_items_names) / sizeof(s_menu_items_names[0])); i++)
  {
    s_menu_items[i] = (SimpleMenuItem){
      .title = s_menu_items_names[i],
    };
  }
}

void setup_menu_sections()
{
  s_menu_sections[0] = (SimpleMenuSection)
  {
    .title = NULL,
      .items = s_menu_items,
      .num_items = sizeof(s_menu_items) / sizeof(s_menu_items[0])
  };
}

static void menu_handler(int index, void *context) {
  switch (index)
  {
    case 0: text_layer_set_text(text_layer, "0"); break;
    case 1: text_layer_set_text(text_layer, "1"); break;
    case 2: text_layer_set_text(text_layer, "2"); break;
    case 3: text_layer_set_text(text_layer, "3"); break;
    case 4: text_layer_set_text(text_layer, "4"); break;
  }
}

static void click_config_provider(void *context) {
  //window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  //window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  //window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_simple_menu_layer = simple_menu_layer_create((GRect) { .origin = { 0, 105 }, .size = { bounds.size.w, 45 }}, window, s_menu_sections, 1, menu_handler);
  layer_add_child(window_layer, (Layer *)s_simple_menu_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(text_layer, "ExampleText");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();

  setup_menu_items();
  setup_menu_sections();
  //window_set_background_color(window, GColorRed);

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
