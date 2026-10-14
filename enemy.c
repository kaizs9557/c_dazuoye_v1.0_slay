#include "marco_struct_def_fucdeclaration.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//判断是否重击
static float attack_calculate_utility(ENTITY* player, ENTITY* enemy, int bout) {
    if (bout == 1) return 1.0f;  // 大鳄虫第一回合必出重击
    float utility = 0.0f;
    utility += bout_utility((float)bout, 4.0f, 20.0f) * 0.4f;
    utility += ((float)enemy->hp / 100.0f) * 0.3f;
    utility += clamp((float)enemy->block / 30.0f, 0.0f, 1.0f) * 0.2f;
    utility += (1.0f - ((float)player->hp / 100.0f)) * 0.2f;
    utility += clamp((float)enemy->strength / 40.0f, 0.0f, 1.0f) * 0.2f;
    return clamp(utility, 0.0f, 1.0f);
}
//执行重击
static void attack_execute(ENTITY* player, ENTITY* enemy) {
    int hp_loss=attributed_strike(enemy, player, enemy->strength);

    printf("大锷虫使用【重击】 造成伤害 %d，玩家格挡剩余 %d，玩家血量 %d", hp_loss, player->block, player->hp);
    sleep(1);
    if (game_state.relics.hasReboundNecklace) {   // 遗物：反击项链
        int rebound = hp_loss/4;
        unattributed_strike(enemy, rebound);
        printf("遗物【反击项链】生效：反弹25%%伤害！敌人剩余血量%d\n", enemy->hp);
        sleep(1);
    }
}

//盾击
static float shield_bash_calculate_utility(ENTITY* player, ENTITY* enemy, int bout) {
    float utility = 0.0f;
    utility += (1.0f - ((float)enemy->hp / 100.0f)) * 0.6f;
    if (enemy->recently_hurt) utility += 0.3f;
    return clamp(utility, 0.0f, 1.0f);
}
static void shield_bash_execute(ENTITY* player, ENTITY* enemy) {
    int hp_loss = attributed_strike(enemy, player, enemy->strength);
    printf("大锷虫使用【盾击】 获得格挡 +5，并造成伤害 %d\n", hp_loss);
    enemy->block += 5;
    enemy->recently_hurt = false;
    sleep(1);
    printf("玩家格挡剩余 %d，玩家血量 %d", player->block, player->hp);
    if (game_state.relics.hasReboundNecklace) {
        int rebound = hp_loss/4;
        unattributed_strike(enemy, rebound);
        printf("遗物【反击项链】生效：反弹25%%伤害！敌人剩余血量%d\n", enemy->hp);
        sleep(1);
    }
}

//怒吼
static float shout_calculate_utility(ENTITY* player, ENTITY* enemy, int bout) {
    float utility = 0.0f;
    utility += (1.0f - clamp((float)enemy->strength / 40.0f, 0.0f, 1.0f)) * 0.4f;
    utility += ((float)player->hp / 100.0f) * 0.4f;
    return clamp(utility, 0.0f, 1.0f);
}
static void shout_execute(ENTITY* player, ENTITY* enemy) {
    printf("大鳄虫使用【吼叫】 力量 +3，格挡 +6\n");
    sleep(1);
    enemy->strength += 3;
    enemy->block += 6;
}

//小史莱姆攻击
static float little_slime_attack_calculate_utility(ENTITY* player, ENTITY* enemy, int bout) {
    float utility = 0.0f;
    utility += bout_utility((float)bout, 4.0f, 20.0f) * 0.4f;
    utility += 1.0f - game_state.enemy_count * 0.4f;
    return clamp(utility, 0.0f, 1.0f);
}
static void little_slime_attack_execute(ENTITY* player, ENTITY* enemy) {
    int hp_loss = attributed_strike(enemy, player, enemy->strength);
    printf("小史莱姆使用【攻击】 造成伤害 %d，玩家格挡剩余 %d，玩家血量 %d", hp_loss, player->block, player->hp);
    sleep(1);
    if (game_state.relics.hasReboundNecklace) {
        int rebound = hp_loss/4;
        unattributed_strike(enemy, rebound);
        printf("遗物【反击项链】生效：反弹25%%伤害！敌人剩余血量%d\n", enemy->hp);
        sleep(1);
    }
}

//小史莱姆刺击
static float little_slime_stab_attack_calculate_utility(ENTITY* player, ENTITY* enemy, int bout) {
    float utility = 0.0f;
    utility += (float)player->block / 100.0f * 0.4f;
    utility += (float)player->hp / 100.0f * 0.3f;
    return clamp(utility, 0.0f, 1.0f);
}
static void little_slime_stab_attack_execute(ENTITY* player, ENTITY* enemy) {
    int hp_loss = attributed_strike(enemy, player, enemy->strength);
    printf("小史莱姆使用【刺击】 造成伤害 %d，玩家格挡剩余 %d，玩家血量 %d", hp_loss, player->block, player->hp);
    sleep(1);
    printf("\n玩家易伤%d+1", player->buff[VUL]);
    buff_cast(player, VUL, 1);//加上一层易伤
    if (game_state.relics.hasReboundNecklace) {
        int rebound = hp_loss/4;
        unattributed_strike(enemy, rebound);
        printf("遗物【反击项链】生效：反弹25%%伤害！敌人剩余血量%d\n", enemy->hp);
        sleep(1);
    }
}

//乐加维林沉睡（前三回合）
static float elite_legavelin_sleep_calculate_utility(ENTITY* player, ENTITY* enemy, int bout) {
    if (bout <= 3) { return 1.0f; }
    return 0.0f;
}
static void legavelin_sleep_execute(ENTITY* player, ENTITY* enemy) {
    printf("乐加维林沉睡中，格挡：%d+8", enemy->block);
    sleep(1);
    enemy->block += 8;
}

//乐加维林重击
static float legavelin_thump_calculate_utility(ENTITY* player, ENTITY* enemy, int bout) {
    float utility = 0.0f;
    if (bout <= 5 && bout > 3) { return 1.0f; }//乐加维林睡醒后必重击
    utility += bout_utility((float)bout, 4.0f, 20.0f) * 0.4f;
    utility += (float)player->hp / 100.0f * 0.3f;//玩家血量越多，越想攻击
    if (enemy->recently_hurt) { utility += 0.3f; }//受伤后愤怒，想反击 
    return clamp(utility, 0.0f, 1.0f);
}
static void legavelin_thump_execute(ENTITY* player, ENTITY* enemy) {
    int dmg = enemy->strength;
    int hp_loss;
    if (enemy->recently_hurt) {
        dmg=dmg*6/5;
        hp_loss = attributed_strike(enemy, player, dmg);
        printf("乐加维林收到攻击，红温了，使用【重击】伤害增加 造成伤害 %d，玩家格挡剩余 %d，玩家血量 %d", hp_loss, player->block, player->hp);
    }
    else {
        hp_loss=attributed_strike(enemy, player, dmg);
        printf("乐加维林使用【重击】 造成伤害 %d，玩家格挡剩余 %d，玩家血量 %d", hp_loss, player->block, player->hp);
    }
    if (game_state.relics.hasReboundNecklace) {
        int rebound = (hp_loss/4);
        unattributed_strike(enemy, rebound);
        printf("遗物【反击项链】生效：反弹25%%伤害！敌人剩余血量%d\n", enemy->hp);
        sleep(1);
    }
}

//乐加维林灵魂抽取
static float legavelin_soul_extraction_calculate_utility(ENTITY* player, ENTITY* enemy, int bout) {
    float utility = 0.0f;
    utility += (1.0f - ((float)enemy->hp / 100.0f)) * 0.3f;
    utility += (player->strength) * 0.3f;
    utility += (player->buff[AGI]) * 0.4f;
    return clamp(utility, 0.0f, 1.0f);
}
static void legavelin_soul_extraction_execute(ENTITY* player, ENTITY* enemy) {
    printf("乐加维林使用灵魂抽取，玩家力量剩余 %d,玩家敏捷剩余 %d", player->strength - 2, player->buff[AGI] - 2);
    sleep(1);
    player->strength -= 2;
    player->buff[AGI] -= 2;
    enemy->hp += 5;
}

//创建ai实体//这里的flag用来决定敌人类型，可以根据level的情况改变
ENERMYEntity* create_ai_entity(int flag) {
    ENERMYEntity* entity = (ENERMYEntity*)malloc(sizeof(ENERMYEntity));
    for (int i = 0; i < ACTION_MAX; ++i) entity->actions[i] = NULL; 
    switch (flag) {
    case GREAT_ALLIGATOR: {
        entity->type = GREAT_ALLIGATOR;
        entity->low_action_count = 0;
        entity->high_action_count = 3;
        break;
    }
    case LITTLE_SLIME: {
        entity->type = LITTLE_SLIME;
        entity->low_action_count = 3;
        entity->high_action_count = 5;
        break;
    }
    case ELITE_MONSTER_LEGAVELIN: {
        entity->type = ELITE_MONSTER_LEGAVELIN;
        entity->low_action_count = 5;
        entity->high_action_count = ACTION_MAX;
        break;
    }
    default: break;
    }
    return entity;
}

void initialize_all_actions(ENERMYEntity* entity) {
    if (entity->type == GREAT_ALLIGATOR) {
        ENERMYAction* attack = (ENERMYAction*)malloc(sizeof(ENERMYAction));
        attack->type = GREAT_ALLIGATOR_ACTION_THump;
        attack->name = "重击";
        attack->calculate_utility = attack_calculate_utility;
        attack->execute = attack_execute;
        entity->actions[GREAT_ALLIGATOR_ACTION_THump] = attack;

        ENERMYAction* shield = (ENERMYAction*)malloc(sizeof(ENERMYAction));
        shield->type = GREAT_ALLIGATOR_ACTION_SHIELD_BASH;
        shield->name = "盾击";
        shield->calculate_utility = shield_bash_calculate_utility;
        shield->execute = shield_bash_execute;
        entity->actions[GREAT_ALLIGATOR_ACTION_SHIELD_BASH] = shield;

        ENERMYAction* shout = (ENERMYAction*)malloc(sizeof(ENERMYAction));
        shout->type = GREAT_ALLIGATOR_ACTION_SHOUT;
        shout->name = "吼叫";
        shout->calculate_utility = shout_calculate_utility;
        shout->execute = shout_execute;
        entity->actions[GREAT_ALLIGATOR_ACTION_SHOUT] = shout;
    }
    else if (entity->type == LITTLE_SLIME) {
        ENERMYAction* attack = (ENERMYAction*)malloc(sizeof(ENERMYAction));
        attack->type = LITTLE_SLIME_ACTION_ATTACK;
        attack->name = " 攻击";
        attack->calculate_utility = little_slime_attack_calculate_utility;
        attack->execute = little_slime_attack_execute;
        entity->actions[LITTLE_SLIME_ACTION_ATTACK] = attack;

        ENERMYAction* stab_attack = (ENERMYAction*)malloc(sizeof(ENERMYAction));
        stab_attack->type = LITTLE_SLIME_ACTION_STAB_ATACK;
        stab_attack->name = "刺击";
        stab_attack->calculate_utility = little_slime_stab_attack_calculate_utility; // 修正：用刺击的计算
        stab_attack->execute = little_slime_stab_attack_execute;
        entity->actions[LITTLE_SLIME_ACTION_STAB_ATACK] = stab_attack;
    }
    else if (entity->type == ELITE_MONSTER_LEGAVELIN) { // 修正：== 不是 =
        ENERMYAction* sleep = (ENERMYAction*)malloc(sizeof(ENERMYAction));
        sleep->type = LEGAVELIN_SLEEP;
        sleep->name = "沉睡";
        sleep->calculate_utility = elite_legavelin_sleep_calculate_utility;
        sleep->execute = legavelin_sleep_execute;
        entity->actions[LEGAVELIN_SLEEP] = sleep;

        ENERMYAction* thump = (ENERMYAction*)malloc(sizeof(ENERMYAction));
        thump->type = ELITE_MONSTER_LEGAVELIN_ACTION_THUMP;
        thump->name = "重击";
        thump->calculate_utility = legavelin_thump_calculate_utility; // 修正：用重击的计算
        thump->execute = legavelin_thump_execute;
        entity->actions[ELITE_MONSTER_LEGAVELIN_ACTION_THUMP] = thump;

        ENERMYAction* soul_extraction = (ENERMYAction*)malloc(sizeof(ENERMYAction));
        soul_extraction->type = ELITE_MONSTER_LEGAVELIN_ACTION_SOUL_EXTRACTION;
        soul_extraction->name = "灵魂提取";
        soul_extraction->calculate_utility = legavelin_soul_extraction_calculate_utility;
        soul_extraction->execute = legavelin_soul_extraction_execute;
        entity->actions[ELITE_MONSTER_LEGAVELIN_ACTION_SOUL_EXTRACTION] = soul_extraction;
    }
    else { printf("error"); }
}

void ai_think(ENERMYEntity* entity, ENTITY* player, ENTITY* enemy, int bout) {
    if (!entity) return;

    float highest_utility = -1.0f;
    ActionType best_action = entity->high_action_count;//默认无行动

    printf("\n=== 敌人AI决策 ===\n");
    printf("敌人: 血量=%d 力量=%d 格挡=%d 回合=%d\n",
        enemy->hp, enemy->strength, enemy->block, bout);

    for (int i = entity->low_action_count; i < entity->high_action_count; i++) {
        ENERMYAction* action = entity->actions[i];
        if (!action) continue;

        float utility = action->calculate_utility(player, enemy, bout);
        printf("  %s: 效用=%.2f\n", action->name, utility);

        if (utility > highest_utility) {
            highest_utility = utility;
            best_action = (ActionType)i;
        }
    }
    sleep(1);
    entity->current_action = best_action;

    if (best_action != entity->high_action_count && entity->actions[best_action]) {
        printf(">>> 敌人选择: %s (%.2f)\n",
            entity->actions[best_action]->name, highest_utility);
    }
    else {
        printf(">>> 敌人没有行动可执行\n");
    }
}

void ai_execute_best_action(ENERMYEntity* entity, ENTITY* player, ENTITY* enemy) {
    if (!entity || entity->current_action == entity->high_action_count) return;
    ENERMYAction* action = entity->actions[entity->current_action];
    if (action) action->execute(player, enemy);
}
//判断战斗胜利
bool if_victory(GAME_STATE* state,Levelconfig*level) {
    // 修复：检查关卡中所有敌人是否都被击败
    for (int i = 0; i < level->total_count; i++) {
        if (state->enemy[i] != NULL && state->enemy[i]->hp > 0) {
            return false;
        }
    }
    return true;
}
// 修正：补充销毁函数
void destroy_ai_entity(ENERMYEntity* entity) {
    if (!entity) return;
    for (int i = 0; i < ACTION_MAX; ++i) {
        free(entity->actions[i]);
    }
    free(entity);
}