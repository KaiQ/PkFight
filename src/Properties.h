#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <stdint.h>
#include <stdlib.h>


enum MENU_SECTIONS
{
  MENU_SECTION_MAIN,
  MENU_SECTION_ATTACK,
  MENU_SECTION_BAG,
  MENU_SECTION_MONSTER
};

enum MENU_ROWS_MAIN
{
  MENU_ROW_MAIN_ATTACK,
  MENU_ROW_MAIN_BAG,
  MENU_ROW_MAIN_MONSTER,
  MENU_ROW_MAIN_RUN
};

enum STATUS
{
  STATUS_NORMAL   = 0,
  STATUS_POISON   = 1,
  STATUS_CONFUSED = 2,
  STATUS_SLEEP    = 4
};


enum TYPE
{
  TYPE_NORMAL,
  TYPE_ROCK,
  TYPE_FIRE,
  TYPE_WATER,
  TYPE_ELECTRO,
  TYPE_GRASS,
  TYPE_DRAGON
};


typedef struct
{
  uint8_t type;
  char*   name;
  float damage;
} attack;


#endif
