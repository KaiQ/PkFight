#include <pebble.h>

static Window *window;
static TextLayer *text_layer;
static SimpleMenuLayer * s_simple_menu_layer;
static SimpleMenuItem s_menu_items[4];
static SimpleMenuSection s_menu_sections[1];

void setup_menu_items();
void setup_menu_sections();

static void menu_handler_attack (int index, void *context) {
    text_layer_set_text(text_layer, "Lets Attack!");
}

static void menu_handler_bag (int index, void *context) {
    text_layer_set_text(text_layer, "Lets look in our bag!");
}

static void menu_handler_monster (int index, void *context) {
    text_layer_set_text(text_layer, "Lets change the Monster!");
}

static void menu_handler_run (int index, void *context) {
    text_layer_set_text(text_layer, "Lets RUN AWAY!!!");
}

void setup_menu_items()
{
  s_menu_items[0] = (SimpleMenuItem){
    .title = "Attack",
    .callback = menu_handler_attack,
  };
  s_menu_items[1] = (SimpleMenuItem){
    .title = "Bag",
    .callback = menu_handler_bag,
  };
  s_menu_items[2] = (SimpleMenuItem){
    .title = "Monster",
    .callback = menu_handler_monster,
  };
  s_menu_items[3] = (SimpleMenuItem){
    .title = "RUN",
    .callback = menu_handler_run,
  };
}

void setup_menu_sections()
{
  s_menu_sections[0] = (SimpleMenuSection)
  {
    .title = NULL,
    .items = s_menu_items,
    .num_items = sizeof(s_menu_items) / sizeof(s_menu_items[0]),
  };
}

static void click_config_provider(void *context) {
  //window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  //window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  //window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void update_proc(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, GColorFromRGB(0, 255, 0));
  graphics_fill_rect(ctx, GRect(90, 105, 30, 3), 0, GCornerNone);
  graphics_fill_rect(ctx, GRect(10, 15, 30, 3), 0, GCornerNone);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_simple_menu_layer = simple_menu_layer_create((GRect) { .origin = { 0, 125 }, .size = { bounds.size.w, 45 }}, window, s_menu_sections, 1, NULL);
  layer_add_child(window_layer, (Layer *)s_simple_menu_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(text_layer, "ExampleText");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
  layer_set_update_proc(window_layer, update_proc);
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();

  setup_menu_items();
  setup_menu_sections();
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
