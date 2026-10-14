#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "marco_struct_def_fucdeclaration.h"

#define MAX_RELIC_NAME_LEN 50
#define MAX_RELIC_DESC_LEN 200 //遗物中文描述
#define MAX_PLAYER_RELICS 10 //可持有的最大遗物数

//我把大部分关于遗物的结构体都放在了头文件中

// //定义遗物结构体//新版本已优化掉
// typedef struct relic
// {
//     int id; //遗物id
//     RELIC_TYPES type; //遗物类型
//     char name[MAX_RELIC_NAME_LEN]; //遗物名称
//     char description[MAX_RELIC_DESC_LEN]; //遗物描述
//     int active; // 是否拥有该遗物
//     void (*effect)(void* gamestate); //函数指针，指向该遗物的具体效果函数
// }Relic;

//接下来有一堆遗物效果函数
// 力量手环 战斗开始获得2点力量
void relic_StrengthBand(GAME_STATE* state) {
    if (!state->relics.hasStrengthBand)
        return;

    if (state->isInCombat && state->combatTurn == 1) {
        printf("遗物【力量手环】生效：获得2点力量！\n");
        state->player.buff[0] += 2;
        printf("当前力量：%d\n", state->player.buff[0]);
        sleep(1);
    }
}

// 铁质盔甲 战斗开始获得3点格挡
void relic_IronArmor(GAME_STATE* state) {
    if (!state->relics.hasIronArmor)
        return;

    if (state->isInCombat && state->combatTurn == 1) {
        printf("遗物【铁质盔甲】生效：获得3点格挡！\n");
        state->player.block += 3;
        printf("当前格挡：%d\n", state->player.block);
        sleep(1);
    }
}
// 锋利匕首 战斗时所有基础攻击牌伤害+1
int relic_Dragger(int baseDamage, GAME_STATE* state) {
    if (state->relics.hasDragger && state->isInCombat) {
        printf("遗物【锋利匕首】生效：攻击伤害+1！\n");
        return baseDamage + 1;
        sleep(1);
    }
    return baseDamage;
}
// 幸运金币 回合结束后获得金币增加
void relic_LuckyCoin(GAME_STATE* state) {
    if (!state->relics.hasLuckyCoin)
        return;

    if (!state->isInCombat) {
        int extraGold = rand() % 5 + 1; // 随机获得1-5金币
        printf("遗物【幸运金币】生效：获得额外%d金币！\n", extraGold);
        state->playerGold += extraGold;
        printf("当前金币：%d\n", state->playerGold);
        sleep(1);
    }
}
//  能量电池 每回合能量+1
void relic_CostBattery(GAME_STATE* state) {
    if (!state->relics.hasCostBattery)
        return;

    if (state->isInCombat) {
        printf("遗物【能量电池】生效：本回合能量上限+1！\n");
        state->playerMaxEnergy += 1;
        state->playerEnergy = state->playerMaxEnergy; // 回满能量
        printf("当前能量：%d/%d\n", state->playerEnergy, state->playerMaxEnergy);
        sleep(1);
    }
}
// 反击项链 受到伤害时，反弹所受伤害的10%
int relic_ReboundNecklace(int damageReceived, GAME_STATE* state,ENTITY* enemy) {
    if (state->relics.hasReboundNecklace && state->isInCombat && damageReceived > 0) {
        int reboundDamage = damageReceived / 10; // 10%反弹伤害
        if (reboundDamage > 0) {
            printf("遗物【反击项链】生效：反弹%d点伤害！\n", reboundDamage);
            enemy->hp -= reboundDamage;
            if (enemy->hp < 0)
                enemy->hp = 0;
            printf("敌人生命值：%d/%d\n", enemy->hp, enemy->max_hp);
            sleep(1);
        }
    }
    return damageReceived;
}
// 起始手牌吊坠 每场战斗第一回合多抽一张牌
int relic_InitialPendant(int baseDrawCount, GAME_STATE* state) {
    if (state->relics.hasInitialPendant && state->isInCombat && state->combatTurn == 1) {
        printf("遗物【起始手牌吊坠】生效：第一回合多抽1张牌！\n");
        sleep(1);
        return baseDrawCount + 1;
    }
    return baseDrawCount;
}
// 燃烧之血 整场战斗结束时回复6点生命
void relic_BurningBlood(GAME_STATE* state) {
    if (!state->relics.hasBurningBlood)
        return;

    if (!state->isInCombat) { // 战斗结束
        printf("遗物【燃烧之血】生效：战斗结束，回复6点生命！\n");
        state->player.hp += 6;
        if (state->player.hp > state->player.max_hp) {
            state->player.hp = state->player.max_hp;
        }
        printf("当前生命值：%d/%d\n", state->player.hp, state->player.max_hp);
        sleep(1);
    }
}
//奇异甜甜圈 最大生命值提升
void relic_StrangeDonut(GAME_STATE* state) {
    if (state->relics.hasStrangeDonut) {  // 这个效果只需要在获得遗物时触发一次
        printf("遗物【奇异甜圈圈】生效：最大生命值提升10点！\n");
        state->player.max_hp += 10;
        state->player.hp += 10; // 回复生命
        printf("最大生命值：%d，当前生命值：%d\n",
            state->player.max_hp, state->player.hp);
        sleep(1);
    }
}

//获得遗物
void acquireRelic(const char* relicName, GAME_STATE* state) {
    printf("\n>>> 获得遗物：【%s】\n", relicName);

    if (strcmp(relicName, "力量手环") == 0) {
        state->relics.hasStrengthBand = true;
    }
    else if (strcmp(relicName, "铁质盔甲") == 0) {
        state->relics.hasIronArmor = true;
    }
    else if (strcmp(relicName, "锋利匕首") == 0) {
        state->relics.hasDragger = true;
    }
    else if (strcmp(relicName, "幸运金币") == 0) {
        state->relics.hasLuckyCoin = true;
    }
    else if (strcmp(relicName, "能量电池") == 0) {
        state->relics.hasCostBattery = true;
    }
    else if (strcmp(relicName, "反击项链") == 0) {
        state->relics.hasReboundNecklace = true;
    }
    else if (strcmp(relicName, "起始手牌吊坠") == 0) {
        state->relics.hasInitialPendant = true;
    }
    else if (strcmp(relicName, "燃烧之血") == 0) {
        state->relics.hasBurningBlood = true;
    }
    else if (strcmp(relicName, "奇异甜圈圈") == 0) {
        state->relics.hasStrangeDonut = true;
        relic_StrangeDonut(state); // 立即生效
    }
    else {
        printf("未知遗物：%s\n", relicName);
        return;
    }

    state->relics.relicCount++;
    printf("当前遗物总数：%d\n", state->relics.relicCount);
    sleep(1);
}
//显示已拥有的遗物
void displayRelics(RELIC_STATUS* relics) {
    printf("\n=== 持有遗物 (%d个) ===\n", relics->relicCount);
    if (relics->hasStrengthBand)
        printf("力量手环 ");
    if (relics->hasIronArmor)
        printf("铁质盔甲 ");
    if (relics->hasDragger)
        printf("锋利匕首 ");
    if (relics->hasLuckyCoin)
        printf("幸运金币 ");
    if (relics->hasCostBattery)
        printf("能量电池 ");
    if (relics->hasReboundNecklace)
        printf("反击项链 ");
    if (relics->hasInitialPendant)
        printf("起始手牌吊坠 ");
    if (relics->hasBurningBlood)
        printf("燃烧之血 ");
    if (relics->hasStrangeDonut)
        printf("奇异甜圈圈 ");
}

// 随机获得遗物执行函数
void select_random_relic(GAME_STATE* state) {
    const char* relic_names[] = {
        "力量手环",
        "铁质盔甲",
        "锋利匕首",
        "幸运金币",
        "能量电池",
        "反击项链",
        "起始手牌吊坠",
        "燃烧之血",
        "奇异甜圈圈"
    };
    int random_index = rand() % 8;//9个遗物

    printf("\n=== 遗物选择 ===\n");
    printf("你获得了遗物：%s\n", relic_names[random_index]);

    acquireRelic(relic_names[random_index], state);
    displayRelics(&state->relics);
    printf("\n================\n");
}

// 应用第一回合开始时的遗物效果
void apply_start_of_combat_relics(GAME_STATE* state) {
    if (state->combatTurn == 1) {
        if (state->relics.hasStrengthBand) {
            printf("遗物【力量手环】生效：获得2点力量！\n");
            state->player.strength += 2;
            printf("当前力量：%d\n", state->player.strength);
            sleep(1);
        }
        if (state->relics.hasDragger) {
            printf("遗物【锋利匕首】生效：获得1点力量！\n");
            state->player.strength += 1;
            printf("当前力量：%d\n", state->player.strength);
            sleep(1);
        }
        if (state->relics.hasIronArmor) {
            printf("遗物【铁质盔甲】生效：获得3点格挡！\n");
            state->player.block += 3;
            printf("当前格挡：%d\n", state->player.block);
            sleep(1);
        }
    }
}