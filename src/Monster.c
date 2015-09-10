#include "Monster.h"


void monster_set_attacks(Monster *monster)
{
  monster->attacks[0] = &s_attacks[rand() % ATTACKS_COUNT];
  monster->attacks[1] = &s_attacks[rand() % ATTACKS_COUNT];
  monster->attacks[2] = &s_attacks[rand() % ATTACKS_COUNT];
  monster->attacks[3] = &s_attacks[rand() % ATTACKS_COUNT];
}

char*    monster_get_attack_name(Monster* monster, uint8_t index)
{
  return monster->attacks[index]->name;
}

Monster* monster_create(char* name, uint8_t level)
{
  Monster *monster = (Monster*)malloc(sizeof(Monster));
  monster->name = name;
  monster->hp_max = level * 5; //TODO
  monster->hp = monster->hp_max;
  monster->level = level;
  monster->status = STATUS_NORMAL;
  monster->type = TYPE_NORMAL;
  monster_set_attacks(monster);
  return monster;
}


uint8_t monster_attack(Monster *monster_1, Monster *monster_2)
{
  if (monster_1->status == STATUS_NORMAL)
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






