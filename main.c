#include "marco_struct_def_fucdeclaration.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void initialize_total_game_state(GAME_STATE* state)
{
    state->player.max_hp = 100;
    state->player.hp = 100;
    state->playerGold = 0;

    // 初始化敌人指针数组为NULL
    for (int i = 0; i < MAX_ENEMY_COUNT; i++) {
        state->enemy[i] = NULL;
    }
    state->enemy_count = 0;

    // 初始化遗物状态
    state->relics.hasStrengthBand = false;
    state->relics.hasIronArmor = false;
    state->relics.hasDragger = false;
    state->relics.hasLuckyCoin = false;
    state->relics.hasCostBattery = false;
    state->relics.hasReboundNecklace = false;
    state->relics.hasInitialPendant = false;
    state->relics.hasBurningBlood = false;
    state->relics.hasStrangeDonut = false;
    state->relics.relicCount = 0;

    state->lib_size = 0;
    // 创建lib库（现阶段已实现33种卡牌功能,后续可继续添加）//最后不会用到三张基础牌，就直接先注释掉了
    // insert_card(CARD_STRIKE, state->lib, &state->lib_size, state->lib_size, 0, COST_STRIKE);
    // insert_card(CARD_BASH, state->lib, &state->lib_size, state->lib_size, 0, COST_BASH);
    insert_card(CARD_ANGER, state->lib, &state->lib_size, state->lib_size, 0, COST_ANGER);
    insert_card(CARD_HEADBUTT, state->lib, &state->lib_size, state->lib_size, 0, COST_HEADBUTT);
    insert_card(CARD_TWIN_STRIKE, state->lib, &state->lib_size, state->lib_size, 0, COST_TWIN_STRIKE);
    insert_card(CARD_POM_STRIKE, state->lib, &state->lib_size, state->lib_size, 0, COST_POM_STRIKE);
    insert_card(CARD_HEAVYBLADE, state->lib, &state->lib_size, state->lib_size, 0, COST_HEAVYBLADE);
    insert_card(CARD_IRON_WAVE, state->lib, &state->lib_size, state->lib_size, 0, COST_IRON_WAVE);
    insert_card(CARD_PFT_STRIKE, state->lib, &state->lib_size, state->lib_size, 0, COST_PFT_STRIKE);
    insert_card(CARD_BOOMERANG, state->lib, &state->lib_size, state->lib_size, 0, COST_BOOMERANG);
    insert_card(CARD_THUNDERCLAP, state->lib, &state->lib_size, state->lib_size, 0, COST_THUNDERCLAP);
    insert_card(CARD_WILD_STRIKE, state->lib, &state->lib_size, state->lib_size, 0, COST_WILD_STRIKE);
    insert_card(CARD_BODYSLAM, state->lib, &state->lib_size, state->lib_size, 0, COST_BODYSLAM);
    insert_card(CARD_CLASH, state->lib, &state->lib_size, state->lib_size, 0, COST_CLASH);
    insert_card(CARD_CLEAVE, state->lib, &state->lib_size, state->lib_size, 0, COST_CLEAVE);
    insert_card(CARD_CLOTHESLINE, state->lib, &state->lib_size, state->lib_size, 0, COST_CLOTHESLINE);
    insert_card(CARD_DROPKICK, state->lib, &state->lib_size, state->lib_size, 0, COST_DROPKICK);
    insert_card(CARD_HEMOKINESIS, state->lib, &state->lib_size, state->lib_size, 0, COST_HEMOKINESIS);
    insert_card(CARD_PUMMEL, state->lib, &state->lib_size, state->lib_size, 0, COST_PUMMEL);
    insert_card(CARD_RAMPAGE, state->lib, &state->lib_size, state->lib_size, 0, COST_RAMPAGE);
    insert_card(CARD_CHARGE, state->lib, &state->lib_size, state->lib_size, 0, COST_CHARGE);
    insert_card(CARD_SEARING_BLOW, state->lib, &state->lib_size, state->lib_size, 0, COST_SEARING_BLOW);
    insert_card(CARD_SEVER_SOUL, state->lib, &state->lib_size, state->lib_size, 0, COST_SEVER_SOUL);
    insert_card(CARD_UPPERCUT, state->lib, &state->lib_size, state->lib_size, 0, COST_UPPERCUT);
    insert_card(CARD_BLOOD4, state->lib, &state->lib_size, state->lib_size, 0, COST_BLOOD4);
    insert_card(CARD_WHIRLWIND, state->lib, &state->lib_size, state->lib_size, 0, COST_WHIRLWIND);
    insert_card(CARD_CARNAGE, state->lib, &state->lib_size, state->lib_size, 0, COST_CARNAGE);
    insert_card(CARD_FEED, state->lib, &state->lib_size, state->lib_size, 0, COST_FEED);
    insert_card(CARD_FIEND_FIRE, state->lib, &state->lib_size, state->lib_size, 0, COST_FIEND_FIRE);
    insert_card(CARD_IMMOLATE, state->lib, &state->lib_size, state->lib_size, 0, COST_IMMOLATE);
    insert_card(CARD_REAPER, state->lib, &state->lib_size, state->lib_size, 0, COST_REAPER);
    insert_card(CARD_BLUDGEON, state->lib, &state->lib_size, state->lib_size, 0, COST_BLUDGEON);
    // insert_card(CARD_BLOCK, state->lib, &state->lib_size, state->lib_size, 0, COST_BLOCK);
    printf("总牌组已成功构建，共%d张牌\n", state->lib_size+3);
    // sleep(1);

    state->deck_size = 0;
    //11张牌进deck
    for (int i = 0; i < 5; i++) {
        insert_card(CARD_STRIKE, state->deck, &state->deck_size, state->deck_size, 0, COST_STRIKE);
    }
    for (int i = 0; i < 5; i++) {
        insert_card(CARD_BLOCK, state->deck, &state->deck_size, state->deck_size, 0, COST_BLOCK);
    }
    for (int i = 0; i < 1; i++) {
        insert_card(CARD_BASH, state->deck, &state->deck_size, state->deck_size, 0, COST_BASH);
    }
    printf("您拥有%d张卡牌！\n", state->deck_size);
    // sleep(1);
}
// 一下很多函数都增加了形式参数level，需要用到total_count这一个变量
void initialize_game_state(GAME_STATE* state, Levelconfig* level) {//初始化需要关卡信息
    // 初始化玩家
    state->player.block = 0;
    state->player.strength = 10;
    state->player.recently_hurt = false;
    for (int i = 0; i < 10; i++) {
        state->player.buff[i] = 0;
    }
    // 初始化敌人 先清空之前的敌人指针
    for (int i = 0; i < MAX_ENEMY_COUNT; i++) {
        if (state->enemy[i] != NULL) {
            free(state->enemy[i]);
            state->enemy[i] = NULL;
        }
    }
    // 初始化敌人//进行修改为了初始化多个敌人
    state->enemy_count = level->total_count; // 修正：设置敌人数量
    for (int i = 0; i < level->total_count; i++) {
        //这里把所有敌人的数值都设计成一样的了，感觉还需要一个函数初始化不同的敌人
        //已新增相应代码
        state->enemy[i] = (ENTITY*)malloc(sizeof(ENTITY)); 

        // 设置不同的属性
        switch (level->enemy_types[i]) {
        case GREAT_ALLIGATOR:
            state->enemy[i]->max_hp = 40;
            state->enemy[i]->hp = 40;
            state->enemy[i]->strength = 12;
            break;
        case LITTLE_SLIME:
            state->enemy[i]->max_hp = 13;
            state->enemy[i]->hp = 13;
            state->enemy[i]->strength = 8;
            break;
        case ELITE_MONSTER_LEGAVELIN:
            state->enemy[i]->max_hp = 109;
            state->enemy[i]->hp = 109;
            state->enemy[i]->strength = 15;
            break;
        }

        state->enemy[i]->block = 0;
        state->enemy[i]->recently_hurt = false;
        for (int b = 0; b < 10; b++) {
            state->enemy[i]->buff[b] = 0;
        }
    }

    // 初始化游戏状态
    state->isInCombat = true;
    state->combatTurn = 0;
    state->currentFloor = level->level_number;//用level代替floor
    state->playerEnergy = 0;
    state->playerMaxEnergy = 3;
    state->cardsPlayedThisTurn = 0;

    // 初始化卡牌系统
    state->pile_size = 0;
    state->hand_size = 0;
    state->discard_size = 0;
    state->graveyard_size = 0;


    // 将deck中的卡牌复制到pile中
    for (int i = 0; i < state->deck_size; i++) {
        copy_card(&state->pile[i], &state->deck[i]);
    }
    state->pile_size = state->deck_size;


    // 初始洗牌
    int* order = (int*)calloc(state->pile_size, sizeof(int));
    random_permutation(0, state->pile_size - 1, order);
    for (int i = 0; i < state->pile_size; i++) {
        CARD temp = state->pile[i];
        state->pile[i] = state->pile[order[i]];
        state->pile[order[i]] = temp;
    }
    printf("抽牌堆已完成洗牌\n");
    free(order);
    // sleep(1);
}

// 显示双方状态
static void print_status(GAME_STATE* state, Levelconfig*level) {      //static表示仅在本文件可见
    printf("\n--- 状态 ---\n");
    printf("玩家: 血量=%d/%d 格挡=%d 力量=%d 能量=%d/%d\n",
        state->player.hp, state->player.max_hp, state->player.block, state->player.strength,
        state->playerEnergy, state->playerMaxEnergy);
    for (int i = 0; i < level->total_count;i++) {
        // 检查敌人是否已被击败（指针为NULL）
        if (state->enemy[i] == NULL) {
            printf("敌人%d: 已击败\n", i+1);
            continue;
        }
        const char* enemy_name = "";
        switch (level->enemy_types[i]) {
        case GREAT_ALLIGATOR: enemy_name = "大鳄虫"; break;
        case LITTLE_SLIME: enemy_name = "小史莱姆"; break;
        case ELITE_MONSTER_LEGAVELIN: enemy_name = "乐加维林"; break;
        }
        printf("敌人%d(%s): 血量=%d/%d 力量=%d 格挡=%d\n",
            i+1,enemy_name,state->enemy[i]->hp, state->enemy[i]->max_hp, state->enemy[i]->strength, state->enemy[i]->block);
    }
    // sleep(1);
}

// 显示手牌
static void print_hand(GAME_STATE* state) {
    printf("\n--- 手牌 (%d/%d) ---\n", state->hand_size, 12);
    for (int i = 0; i < state->hand_size; i++) {
        const char* card_name = "";
        switch (state->hand[i].type) {
        case CARD_STRIKE: card_name = "打击"; break;
        case CARD_BASH: card_name = "重击"; break;
        case CARD_ANGER: card_name = "愤怒"; break;
        case CARD_HEADBUTT: card_name = "头槌"; break;
        case CARD_HEAVYBLADE: card_name = "重刃"; break;
        case CARD_IRON_WAVE: card_name = "铁波"; break;
        case CARD_PFT_STRIKE: card_name = "完美打击"; break;
        case CARD_POM_STRIKE: card_name = "剑柄打击"; break;
        case CARD_BOOMERANG: card_name = "回旋镖"; break;
        case CARD_THUNDERCLAP: card_name = "雷鸣攻击"; break;
        case CARD_TWIN_STRIKE: card_name = "双重打击"; break;
        case CARD_WILD_STRIKE: card_name = "狂野打击"; break;
        case CARD_BODYSLAM: card_name = "全身撞击"; break;
        case CARD_CLASH: card_name = "交锋"; break;
        case CARD_CLEAVE: card_name = "顺劈斩"; break;
        case CARD_CLOTHESLINE: card_name = "金刚臂"; break;
        case CARD_DROPKICK: card_name = "飞身踢"; break;
        case CARD_HEMOKINESIS: card_name = "御血术"; break;
        case CARD_PUMMEL: card_name = "连续拳"; break;
        case CARD_RAMPAGE: card_name = "暴走"; break;
        case CARD_CHARGE: card_name = "无谋冲锋"; break;
        case CARD_SEARING_BLOW: card_name = "灼热攻击"; break;
        case CARD_SEVER_SOUL: card_name = "断魂斩"; break;
        case CARD_UPPERCUT: card_name = "上勾拳"; break;
        case CARD_BLOOD4: card_name = "以血还雪"; break;
        case CARD_WHIRLWIND: card_name = "旋风斩"; break;
        case CARD_CARNAGE: card_name = "残杀"; break;
        case CARD_FEED: card_name = "狂宴"; break;
        case CARD_FIEND_FIRE: card_name = "恶魔之焰"; break;
        case CARD_IMMOLATE: card_name = "幡祭"; break;
        case CARD_REAPER: card_name = "死亡收割"; break;
        case CARD_BLUDGEON: card_name = "重锤"; break;
        case CARD_BLOCK: card_name = "格挡"; break;
        default: card_name = "未知卡牌"; break;
        }
        printf("%d. %s (消耗能量: %d) ", i + 1, card_name, state->hand[i].cost);
        if (state->hand[i].upgraded) printf(" [升级]");
        printf("\n");
    }
    // sleep(1);
}

// 新回合开始,重置并显示各项参数
static void start_new_turn(GAME_STATE* state, Levelconfig* level) {
    state->combatTurn++;
    state->playerEnergy = state->playerMaxEnergy;
    state->cardsPlayedThisTurn = 0;
    state->player.block = 0;

    // 遗物能量电池（每回合能量+1）
    if (state->relics.hasCostBattery && state->isInCombat&& state->combatTurn == 1) {
        printf("遗物【能量电池】生效：能量上限+1！\n");
        state->playerMaxEnergy += 1;
        state->playerEnergy = state->playerMaxEnergy; // 回满能量
        printf("当前能量：%d/%d\n", state->playerEnergy, state->playerMaxEnergy);
        // sleep(1);
    }
    // 遗物起始手牌吊坠（第一回合多抽一张牌）
    int draw_count = 5;
    if (state->relics.hasInitialPendant && state->isInCombat && state->combatTurn == 1) {
        printf("遗物【起始手牌吊坠】生效：第一回合多抽1张牌！\n");
        draw_count = 6;
        // sleep(1);
    }

    // 抽牌
    printf("\n=== 第 %d 回合开始 ===\n", state->combatTurn);
    printf("抽取%d张牌...\n", draw_count);
    draw_card(state, draw_count);
    // sleep(1);

    // 显示双方状态和手牌
    print_status(state,level);
    print_hand(state);
}



// 获胜后从lib中抽牌
CARD* get_random_cards_from_lib(GAME_STATE* state, int count) {

    // 保护性检查
    if (!state || state->lib_size <= 0 || count <= 0) return NULL;
    if (count > state->lib_size) count = state->lib_size;

    CARD* random_cards = (CARD*)malloc(sizeof(CARD) * count);
    if (!random_cards) return NULL;

    // 数组用来存储lib中卡牌的相应序号
    int* indices = (int*)malloc(sizeof(int) * state->lib_size);
    if (!indices) { free(random_cards); return NULL; }
    for (int i = 0; i < state->lib_size; i++) {
        indices[i] = i;
    }

    // 打乱
    random_permutation(0, state->lib_size - 1, indices);

    for (int i = 0; i < count; i++) {
        copy_card(&random_cards[i], &state->lib[indices[i]]);
    }
    free(indices);
    return random_cards;
}

// 显示卡牌选择界面
void display_card_selection(CARD* cards, int count) {
    printf("\n=== 胜利奖励：选择一张卡牌加入牌组 ===\n");
    printf("你可以选择一张卡牌加入你的牌组，或者选择不添加任何卡牌\n\n");
    printf("0. 不选择任何卡牌\n");
    for (int i = 0; i < count; i++) {
        printf("%d. ", i + 1);

        // 显示卡牌名称
        const char* card_name = "";
        switch (cards[i].type) {
            case CARD_ANGER: card_name = "愤怒"; break;
            case CARD_HEADBUTT: card_name = "头槌"; break;
            case CARD_HEAVYBLADE: card_name = "重刃"; break;
            case CARD_IRON_WAVE: card_name = "铁波"; break;
            case CARD_PFT_STRIKE: card_name = "完美打击"; break;
            case CARD_POM_STRIKE: card_name = "剑柄打击"; break;
            case CARD_BOOMERANG: card_name = "回旋镖"; break;
            case CARD_THUNDERCLAP: card_name = "雷鸣攻击"; break;
            case CARD_TWIN_STRIKE: card_name = "双重打击"; break;
            case CARD_WILD_STRIKE: card_name = "狂野打击"; break;
            case CARD_BODYSLAM: card_name = "全身撞击"; break;
            case CARD_CLASH: card_name = "交锋"; break;
            case CARD_CLEAVE: card_name = "顺劈斩"; break;
            case CARD_CLOTHESLINE: card_name = "金刚臂"; break;
            case CARD_DROPKICK: card_name = "飞身踢"; break;
            case CARD_HEMOKINESIS: card_name = "御血术"; break;
            case CARD_PUMMEL: card_name = "连续拳"; break;
            case CARD_RAMPAGE: card_name = "暴走"; break;
            case CARD_CHARGE: card_name = "无谋冲锋"; break;
            case CARD_SEARING_BLOW: card_name = "灼热攻击"; break;
            case CARD_SEVER_SOUL: card_name = "断魂斩"; break;
            case CARD_UPPERCUT: card_name = "上勾拳"; break;
            case CARD_BLOOD4: card_name = "以血还雪"; break;
            case CARD_WHIRLWIND: card_name = "旋风斩"; break;
            case CARD_CARNAGE: card_name = "残杀"; break;
            case CARD_FEED: card_name = "狂宴"; break;
            case CARD_FIEND_FIRE: card_name = "恶魔之焰"; break;
            case CARD_IMMOLATE: card_name = "幡祭"; break;
            case CARD_REAPER: card_name = "死亡收割"; break;
            case CARD_BLUDGEON: card_name = "重锤"; break;
        }
        printf("%s", card_name);

        // 显示能量消耗
        printf(" (消耗能量: %d)\n", cards[i].cost);
    }
    printf("请选择 (0-%d): ", count);
}
// 将选中的卡牌加入deck
void add_selected_card_to_deck(GAME_STATE* state, CARD card) {
    insert_card(card.type, state->deck, &state->deck_size, state->deck_size, card.upgraded, card.cost);
    printf("已将 %s 加入牌组！\n", get_card_name(card.type));
    // sleep(1);
}

GAME_STATE game_state;//因为在头文件中用了extern，所以声明不能放在main中


int main(void) {
    srand((unsigned)time(NULL));//随机数函数初始化
    FILE* log=fopen("log.txt", "a");
    wlog(log, "game start");
    printf("=== 丐版杀戮尖塔卡牌战斗 ===\n");
    printf("项目作者：\n胡家睿 251880451 技术科学试验班\n项健羽 251880312 技术科学试验班\n冒吉宸 251230032 临床医学（卓越医师班）\n贾晨宇 251830095 理科试验班（地球科学与资源环境类）\n");
    printf("每回合抽取相应数量牌，初始默认3点能量\n");
    printf("输入卡牌编号出牌，输入0结束出牌，输入 quit 退出游戏\n");
    sleep(1);

    initialize_total_game_state(&game_state);
    wlog(log, "initialize total gamestate");
    int current_level=1;//结束战斗后进行level++
    bool game_continue = true;

    while (game_continue){
        wlog(log, "level start");
        printf("\n=== 第 %d 关开始 ===\n", current_level);
        Levelconfig* level = create_level(current_level);//创建关卡

        initialize_game_state(&game_state, level);
        wlog(log, "initialize game state");
        // 每局开始前随机获得一个遗物（若后续有多关卡可相应改变）
        select_random_relic(&game_state);

        if (game_state.relics.hasStrangeDonut&&game_state.combatTurn==1) {
            game_state.player.max_hp += 5;
            game_state.player.hp += 5;
        }
        //敌人ai标志位之后确定flag选取标准
        // 初始化敌人AI
        ENERMYEntity* enemy_ai[MAX_ENEMY_COUNT];
        wlog(log, "initialize enemy AI");

        for (int i = 0; i < level->total_count; i++){
            enemy_ai[i] = create_ai_entity(level->enemy_types[i]);
            initialize_all_actions(enemy_ai[i]);
        }//初始化多个敌人；
        wlog(log, "initialize enemies");

        start_new_turn(&game_state,level);
        apply_start_of_combat_relics(&game_state);// 应用第一回合开始时的遗物效果

        bool level_victory = false;
        bool level_defeat = false;

        while (!level_victory && !level_defeat) {

            //减少buff层数，清理格挡
            for (int i=0; i<game_state.enemy_count; i++) {
                if (game_state.enemy[i]==NULL){continue;}
                game_state.enemy[i]->block=0;
                for (int k=0;k<10;k++) {
                    if (k!=STR&&k!=AGI&&k!=HMI&&k!=RTE&&game_state.enemy[i]->buff[k]>0) {
                        game_state.enemy[i]->buff[k]--;
                    }
                }
            }

            game_state.player.block=0;
            for (int k=0;k<10;k++) {
                if (k!=STR&&k!=AGI&&k!=HMI&&k!=RTE&&game_state.player.buff[k]>0) {
                    game_state.player.buff[k]--;
                }
            }

            // 玩家回合
            bool player_turn = true;
            while (player_turn) {
                printf("\n能量: %d/%d | ", game_state.playerEnergy, game_state.playerMaxEnergy);
                printf("输入卡牌编号 (1-%d) 或 0 结束回合: ", game_state.hand_size);

                char input[60] = "\0";   //本来想用gets的，但奈何我创建项目选了C11标准，然后发现gets被删了（恼）
                if (!fgets(input, 60, stdin)) {  //于是学习了一下fgets，大家可以网上搜一下用法
                    printf("输入错误，请重新输入！\n");
                    continue;
                }
                input[strcspn(input, "\r\n")] = 0; //这步将回车换行改为/0，找了好久bug，问了好久ai才明白（哭）

                if (strcmp(input, "quit") == 0) {
                    wlog(log, "game end");
                    fclose(log);
                    printf("游戏结束\n");
                    return 0;
                }

                if (strcmp(input, "0") == 0) {
                    printf("结束回合\n");
                    player_turn = false;
                    break;
                }

                int card_index = atoi(input) - 1; //哈哈哈居然有这样好用的函数被我发现了，把字符串数字直接转换为整型
                if (card_index >= 0 && card_index < game_state.hand_size) {
                    if (game_state.hand[card_index].type>=75) {
                        printf("无法打出这张状态牌！");
                        continue;
                    }
                    if (game_state.hand[card_index].cost > game_state.playerEnergy) {
                        printf("能量不足！需要 %d 能量，当前只有 %d 能量\n",
                            game_state.hand[card_index].cost, game_state.playerEnergy);
                        continue;
                    }

                    printf("打出 %s\n", get_card_name(game_state.hand[card_index].type));
                    // 修改1: 为多敌人系统添加目标选择
                    // 显示可攻击的敌人列表
                    if (game_state.hand[card_index].type==CARD_BLOCK) {
                        execute_cards(&game_state, NULL, &game_state.hand[card_index]);
                        goto cardend;
                    }
                    printf("选择攻击目标:\n");
                    int alive_enemies = 0;
                    for (int i = 0; i < level->total_count; i++) {
                        if (game_state.enemy[i] != NULL && game_state.enemy[i]->hp > 0) {
                            printf("%d. 敌人%d ", i+1, i+1);
                            const char* enemy_name = "";
                            switch (level->enemy_types[i]) {
                            case GREAT_ALLIGATOR: enemy_name = "大鳄虫"; break;
                            case LITTLE_SLIME: enemy_name = "小史莱姆"; break;
                            case ELITE_MONSTER_LEGAVELIN: enemy_name = "乐加维林"; break;
                            }
                            printf("(%s, HP: %d/%d)\n", enemy_name, game_state.enemy[i]->hp, game_state.enemy[i]->max_hp);
                            alive_enemies++;
                        }
                    }

                    if (alive_enemies == 0) {
                        level_victory = true;
                        break;
                    }
                    // 获取玩家选择的敌人
                    int target_choice = -1;
                    while (target_choice < 0 || target_choice >= level->total_count ||
                           game_state.enemy[target_choice] == NULL || game_state.enemy[target_choice]->hp <= 0)
                    {
                        printf("请输入目标编号 (1-%d): ", level->total_count);
                        char target_input[10];
                        if (fgets(target_input, sizeof(target_input), stdin)) {
                            target_input[strcspn(target_input, "\r\n")] = 0;
                            target_choice = atoi(target_input) - 1;
                        }
                    }
                    execute_cards(&game_state, game_state.enemy[target_choice], &game_state.hand[card_index]);
                    // 检查被攻击的敌人是否被击败
                    if (game_state.enemy[target_choice] != NULL && game_state.enemy[target_choice]->hp <= 0) {
                        printf("敌人%d被击败！\n", target_choice+1);
                        free(game_state.enemy[target_choice]);  // 释放内存
                        game_state.enemy[target_choice] = NULL; // 标记为NULL
                    }

                    cardend:
                    //弃牌：
                    int card_type = get_card_type(game_state.hand[card_index].type);
                    if (card_type == 0) {
                        discard_card(&game_state, game_state.hand, &game_state.hand_size, card_index);
                    }
                    else if (card_type == 1 || card_type == 2) {
                        // 消耗或虚无放入graveyard
                        burn_card(&game_state, card_index);
                    }
                    game_state.cardsPlayedThisTurn++;


                    // for (int i = 0; i < level->total_count; i++) {
                    //     if (game_state.enemy[i] != NULL && game_state.enemy[i]->hp <= 0) {
                    //         printf("敌人%d被击败！\n", i+1);
                    //         free(game_state.enemy[i]);  // 释放内存
                    //         game_state.enemy[i] = NULL; // 标记为NULL
                    //     }
                    // }
                    bool all_enemies_defeated = true;
                    for (int i = 0; i < level->total_count; i++) {
                        if (game_state.enemy[i] != NULL) {
                            all_enemies_defeated = false;
                            break;
                        }
                    }
                    if (all_enemies_defeated) {
                        level_victory = true;
                        break;
                    }

                    print_status(&game_state,level);
                    if (game_state.hand_size > 0) {
                        print_hand(&game_state);
                    }
                    else {
                        printf("手牌已空\n");
                    }
                }
                else {
                    printf("无效输入\n");
                }
            }
            if (level_victory) {
                break;
            }

            // 战斗是否结束(再检查一遍)
            if (if_victory(&game_state,level)){
                //同上//改为多敌人判断函数
                level_victory = true;
                break;
            }

            // 敌人回合
            printf("\n--- 敌人回合 ---\n");
            for (int i = 0; i < level->total_count; i++) {
                // 只对存活的敌人执行ai行动
                if (game_state.enemy[i] != NULL) {
                    ai_think(enemy_ai[i], &game_state.player, game_state.enemy[i], game_state.combatTurn);
                    ai_execute_best_action(enemy_ai[i], &game_state.player, game_state.enemy[i]);
                }
            }
            if (game_state.player.hp <= 0) {
                printf("你被敌人击败了！");
                level_defeat = true;
                break;
            }

            // 将所有剩余手牌放入弃牌堆或消耗牌堆
            while (game_state.hand_size > 0) {
                // 获取卡牌类型
                int card_type = get_card_type(game_state.hand[0].type);

                if (card_type == 0||card_type == 1 ) {
                    //消耗牌正常洗牌
                    discard_card(&game_state, game_state.hand, &game_state.hand_size, 0);
                }
                else if (card_type == 2) {
                    // 虚无放入graveyard
                    burn_card(&game_state, 0);
                }
            }
            // 开始新回合
            start_new_turn(&game_state,level); //重置并显示各项参数
        }

        // 显示本场战斗最终结果（注意：在释放敌人内存之前显示，避免访问已释放指针）
        print_status(&game_state,level);

        // 清理当前关卡的敌人AI内存和敌人实体
        for (int j = 0; j < level->total_count; j++) {
            destroy_ai_entity(enemy_ai[j]);
            if (game_state.enemy[j] != NULL) {
                free(game_state.enemy[j]);
                game_state.enemy[j] = NULL;
            }
        }
        if (game_state.player.hp <= 0 && if_victory(&game_state,level)) {
            wlog(log, "player died with enemies");
            printf("\n你与同归于尽\n");
        }

        if (level_victory)
        {
            // 应用燃烧之血（战斗结束回复生命）
            if (game_state.relics.hasBurningBlood) {
                printf("遗物【燃烧之血】生效：战斗结束，回复6点生命！\n");
                game_state.player.hp += 6;
                if (game_state.player.hp > game_state.player.max_hp) {
                    game_state.player.hp = game_state.player.max_hp;
                }
                printf("当前生命值：%d/%d\n", game_state.player.hp, game_state.player.max_hp);
                // sleep(1);
            }

            game_state.playerGold += 5;
            if (game_state.relics.hasLuckyCoin)
                game_state.playerGold += 3;
            printf("\n你赢下了战斗！太有实力了！\n获得金币%d个！\n", game_state.playerGold);
            // sleep(1);
            wlog(log, "player won the battle!");
            CARD* reward_cards = get_random_cards_from_lib(&game_state, 3);
            if (reward_cards != NULL)
            {
                display_card_selection(reward_cards, 3);
                // 获取玩家选择
                char input[10];
                if (fgets(input, sizeof(input), stdin)) {
                    input[strcspn(input, "\r\n")] = 0;
                    int choice = atoi(input);
                    if (choice >= 1 && choice <= 3) {
                        add_selected_card_to_deck(&game_state, reward_cards[choice - 1]);
                        wlog(log, "add card %s to the deck", get_card_name(game_state.deck[game_state.deck_size-1].type));
                    }
                    else if (choice == 0) {
                        printf("你选择不添加任何卡牌\n");
                    }
                    else {
                        printf("无效选择\n");
                    }
                }
                free(reward_cards);
            }
            if (current_level<=5){
                printf("\n是否继续下一关？(y/n): ");
                char input[10];
                if (fgets(input, sizeof(input), stdin)) {
                    input[strcspn(input, "\r\n")] = 0;
                    if (strcmp(input, "y") == 0 || strcmp(input, "Y") == 0) {
                        current_level++;
                        printf("进入第 %d 关！\n", current_level);
                    }
                    else {
                        printf("游戏结束！你通过了 %d 关\n", current_level);
                        game_continue = false;
                    }
                }
            }
            if (current_level > 5) {
                wlog(log, "player make it to the end");
                printf("\n恭喜你通关了所有关卡！\n");
                game_continue = false;
            }
        }
        else {
            wlog(log, "player lost the game");
            printf("\n你输了，再试一次吧！\n");
            game_continue = false;
        }
    free(level);
    }
    wlog(log, "program stop running");
    fclose(log);
    return 0;
}