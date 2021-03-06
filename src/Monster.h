#ifndef MONSTER_H
#define MONSTER_H

#include <stdint.h>
#include <stdlib.h>
#include "Properties.h"
#include "Attack.h"


typedef struct
{
  char*    name;
  uint16_t hp_max;
  int16_t  hp;
  uint8_t  level;
  uint8_t  status;
  uint8_t  type;
  Attack*  attacks[4];
} Monster;


Monster* monster_create (char* name, uint8_t level);
uint8_t  monster_attack (Monster *monster1, Attack* attack, Monster *monster2);
uint8_t  monster_get_life_percent(Monster *monster, uint8_t max);
char*    monster_get_attack_name(Monster* monster, uint8_t index);
Attack*  monster_get_attack(Monster* monster, uint8_t index);

#endif
