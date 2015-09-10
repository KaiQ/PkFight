#ifndef ATTACK_H
#define ATTACK_H

#include "Properties.h"
#include "Monster.h"

#define ATTACKS_COUNT 10


static attack s_attacks[ATTACKS_COUNT] =
{
  {
    .name = "Geowurf",
    .type = TYPE_NORMAL,
    .damage = 0.3
  },
  {
    .name = "Donnerschlag",
    .type = TYPE_ELECTRO,
    .damage = 0.6
  },
  {
    .name = "Steinwurf",
    .type = TYPE_ROCK,
    .damage = 0.5
  },
  {
    .name = "Flammenwurf",
    .type = TYPE_FIRE,
    .damage = 0.9
  },
  {
    .name = "Hydropumpe",
    .type = TYPE_WATER,
    .damage = 1.0
  },
  {
    .name = "Rasierblatt",
    .type = TYPE_GRASS,
    .damage = 0.4
  },
  {
    .name = "Drachenwut",
    .type = TYPE_DRAGON,
    .damage = 1
  },
  {
    .name = "Ultraschall",
    .type = TYPE_NORMAL,
    .damage = 0.0
  },
  {
    .name = "Hypnose",
    .type = TYPE_NORMAL,
    .damage = 0.0
  },
  {
    .name = "Giftwolke",
    .type = TYPE_NORMAL,
    .damage = 0.1
  }
};



#endif

