#include "Monster.h"


Monster* monster_create(char* name, uint8_t level)
{
  Monster *monster = (Monster*)malloc(sizeof(Monster));
  monster->name = name;
  monster->hp_max = level * 5; //TODO
  monster->hp = monster->hp_max;
  monster->level = level;
  monster->status = STATUS_NORMAL;
  monster->type = TYPE_NORMAL;
  return monster;
}


uint8_t monster_attack(Monster *monster_1, Monster *monster_2)
{
  monster_2->hp -= 5; //TODO Attack calculation
  return monster_2->hp;
}


uint8_t monster_get_life_percent(Monster *monster, uint8_t max)
{
  if (monster->hp <= 0)
    return 0;
  if (monster->hp == monster->hp_max)
    return max;
  double ret = monster->hp * max / monster->hp_max;
  if (ret <= 0)
    ret = 1;
  if (ret >= max)
    ret = 1;
  return ret;
}






