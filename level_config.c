#include<stdio.h>
#include<stdlib.h> // 修正：malloc 需要
#include "marco_struct_def_fucdeclaration.h"
Levelconfig* create_level(int level_number) {           //改为接受等级参数
    Levelconfig* level = (Levelconfig*)malloc(sizeof(Levelconfig));
    level->level_number = level_number;

    switch (level_number) {
    case 1:
        level->level_name = "虫窝";
        level->total_count = 1;
        level->enemy_types[0] = GREAT_ALLIGATOR;
        level->reward = 10;
        break;

    case 2:
        level->level_name = "史莱姆巢穴";
        level->total_count = 2;
        level->enemy_types[0] = LITTLE_SLIME;
        level->enemy_types[1] = LITTLE_SLIME;
        level->reward = 15;
        break;

    case 3:
        level->level_name = "精英挑战";
        level->total_count = 1;
        level->enemy_types[0] = ELITE_MONSTER_LEGAVELIN;
        level->reward = 25;
        break;

    case 4:
        level->level_name = "混合敌人";
        level->total_count = 2;
        level->enemy_types[0] = GREAT_ALLIGATOR;
        level->enemy_types[1] = LITTLE_SLIME;
        level->reward = 20;
        break;

    case 5:
        level->level_name = "最终试炼";
        level->total_count = 3;
        level->enemy_types[0] = GREAT_ALLIGATOR;
        level->enemy_types[1] = LITTLE_SLIME;
        level->enemy_types[2] = ELITE_MONSTER_LEGAVELIN;
        level->reward = 50;
        break;
    }

    printf("创建关卡 %d: %s (敌人数量: %d)\n",
           level->level_number, level->level_name, level->total_count);
    return level;
}