#include <stdint.h>
#include <stdlib.h>


typedef struct {
  char*   name;
  uint16_t hp_max;
  int16_t hp;
  uint8_t level;
  uint8_t status;
  uint8_t type;
} Monster;


enum STATUS {
  STATUS_NORMAL   = 0,
  STATUS_POISON   = 1,
  STATUS_CONFUSED = 2,
  STATUS_SLEEP    = 4
};


enum TYPE {
  TYPE_NORMAL,
  TYPE_ROCK,
  TYPE_FIRE,
  TYPE_WATER,
  TYPE_ELECTRO,
  TYPE_GRASS,
  TYPE_DRAGON
};


Monster* monster_create (char* name, uint8_t level);
uint8_t  monster_attack (Monster *monster1, Monster *monster2);
uint8_t  monster_get_life_percent(Monster *monster, uint8_t max);



