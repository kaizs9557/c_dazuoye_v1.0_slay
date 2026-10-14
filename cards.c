#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "marco_struct_def_fucdeclaration.h"

//此函数用于返回卡牌种类：0，普通卡牌；1，消耗；2：虚无
int get_card_type(CARD_TYPES type) {
    switch (type) {
        case 26: {
            return 2;
        }
        case 27:
        case 28:
        case 30: {
            return 1;
        }
        default: {
            return 0;
        }
    }
}

//此函数用于返回卡牌名
const char* get_card_name(CARD_TYPES card_type) {  //感觉有点“字符串变量”的味道了，我在说什么（乐
    switch (card_type) {
        case CARD_STRIKE: return "打击";
        case CARD_BASH: return "痛击";
        case CARD_ANGER: return "愤怒";
        case CARD_HEADBUTT: return "头槌";
        case CARD_HEAVYBLADE: return "重刃";
        case CARD_IRON_WAVE: return "铁波";
        case CARD_PFT_STRIKE: return "完美打击";
        case CARD_POM_STRIKE: return "剑柄打击";
        case CARD_BOOMERANG: return "回旋镖";
        case CARD_THUNDERCLAP: return "雷鸣攻击";
        case CARD_TWIN_STRIKE: return "双重打击";
        case CARD_WILD_STRIKE: return "狂野打击";
        case CARD_BODYSLAM: return "全身撞击";
        case CARD_CLASH: return "交锋";
        case CARD_CLEAVE: return "顺劈斩";
        case CARD_CLOTHESLINE: return "金刚臂";
        case CARD_DROPKICK: return "飞身踢";
        case CARD_HEMOKINESIS: return "御血术";
        case CARD_PUMMEL: return "连续拳";
        case CARD_RAMPAGE: return "暴走";
        case CARD_CHARGE: return "无谋冲锋";
        case CARD_SEARING_BLOW: return "灼热攻击";
        case CARD_SEVER_SOUL: return "断魂斩";
        case CARD_UPPERCUT: return "上勾拳";
        case CARD_BLOOD4: return "以血还雪";
        case CARD_WHIRLWIND: return "旋风斩";
        case CARD_CARNAGE: return "残杀";
        case CARD_FEED: return "狂宴";
        case CARD_FIEND_FIRE: return "恶魔之焰";
        case CARD_IMMOLATE: return "幡祭";
        case CARD_REAPER: return "死亡收割";
        case CARD_BLUDGEON: return "重锤";
        case CARD_BLOCK: return "格挡";
        default: return "未知卡牌";
    }
}

void copy_card(CARD *dest, CARD *source) {
    dest->upgraded=source->upgraded;
    dest->type=source->type;
    dest->cost=source->cost;
    dest->rampage_extra_dmg=source->rampage_extra_dmg;
}

//生成从i到j的随机排列
void random_permutation(int i, int j, int order[]) {
    if (i>j) {
        return;
    }
    int n=j-i+1;
    for(int k=0; k<n; k++) {
        order[k]=i+k;
    }
    //随机洗牌
    for(int k=n-1; k>0; k--) {
        // 生成0到k之间的随机索引
        int r = rand()%(k + 1);
        int temp=order[k];
        order[k]=order[r];
        order[r]=temp;
    }
}

//将弃牌堆打乱放入抽牌堆
void shuffle(GAME_STATE* state) {
    int order[state->discard_size];
    random_permutation(0, state->discard_size-1, order);
    for (int i=0;i<state->discard_size;i++) {
        copy_card(&state->pile[i], &state->discard[order[i]]);
    }
    state->pile_size=state->discard_size;
    state->discard_size=0;
}

//从pile的尾端抽牌（接受抽牌数量draw_count)
int draw_card(GAME_STATE* state,const int draw_count) {
    int rest=draw_count;
    while ((state->pile_size!=0||state->discard_size!=0)&&rest!=0) {
        //手牌满时返回-1
        if (state->hand_size>=12) {
            return -1;
        }
        if (!state->pile_size) {
            shuffle(state);
        }
        for (;rest>0&&state->pile_size>0;rest--) {
            copy_card(&state->hand[state->hand_size++],&state->pile[state->pile_size-1]);
            state->pile_size--;
        }
    }
    //抽满或抽牌堆与弃牌堆都没牌时，返回0
    return 0;
}

//消耗手牌中第i张牌，并将其后的牌依次前移一位；这个函数已经内置修改size
void burn_card(GAME_STATE* state,int i) {
    copy_card(&state->hand[i],&state->graveyard[state->graveyard_size++]);
    for (int k=i;k<state->hand_size-1;k++) {
            copy_card(&state->hand[k],&state->hand[k+1]);
    }
    state->hand_size--;
}

//将第i张牌放入弃牌堆，card_array为这张牌所在的牌堆，array_size指向对应牌堆的大小，
void discard_card(GAME_STATE* state,CARD card_array[], int* array_size, int i) {
    copy_card(&state->discard[state->discard_size++],&card_array[i]);
    for (int k=i;k<*array_size-1;k++) {
        copy_card(&card_array[k],&card_array[k+1]);
    }
    *array_size-=1;
}

//把类型为type的卡牌插入card_array[]的第i位，并指明是否升级与cost值
//是的，它接受6个参数。  //很好大多数函数在文件合并后都多了一个参数，而这个函数并没有，依旧保持6个
//一坨屎。
void insert_card(CARD_TYPES type,CARD card_array[],int *array_size, int i, int upgraded, int cost) {
    for (int k=*array_size;k>i;k--) {
        copy_card(&card_array[k],&card_array[k-1]);
    }
    card_array[i].upgraded=upgraded;
    card_array[i].type=type;
    card_array[i].cost=cost;
    card_array[i].rampage_extra_dmg = 0;
    *array_size+=1;
}

//无来源伤害，这里不计算buff的加成（有药水之类不会被buff影响的东西）
int unattributed_strike(ENTITY *target, int damage) {
    int pri=target->hp;
    if (target->block>=damage) {
        target->block-=damage;
    }
    else if (damage-target->block<target->hp) {
        target->hp-=damage-target->block;
        target->block = 0; //新增
    }
    else {
        target->hp=0;
    }
    return pri-target->hp;
}

//有来源伤害，这个包括buff加成
int attributed_strike(ENTITY *caster, ENTITY *target, int damage) {
    int pri=target->hp;
    damage+=caster->buff[STR];
    if (target->buff[VUL]) {
        damage*=2;
    }
    if (caster->buff[WEK]) {
        damage=damage*3/4;
    }
    unattributed_strike(target, damage);
    if (target->buff[THO] > 0){
        unattributed_strike(caster, target->buff[THO]);
    }

    return pri-target->hp;
}

//格挡计算
void block(ENTITY* caster, int defence) {
    defence+=caster->buff[AGI];
    if (caster->buff[BRK]) {
        defence=defence*3/4;
    }
    caster->block+=defence;
}

//给予buff，层数不超过999
void buff_cast(ENTITY *target, int buff_id, int count) {
    //若为负面buff且目标有人工制品，则抵消效果并减少一层人工制品
    if (target->buff[HMI]&&buff_id>=2&&buff_id<=5) {
        target->buff[HMI]--;
    }
    else if (target->buff[buff_id]+count>999) {
        target->buff[buff_id]=999;
    }
    else {
        target->buff[buff_id]+=count;
    }
}

//玩家打出卡牌
void execute_cards(GAME_STATE* state,ENTITY* target, CARD *card) {
    if (state->playerEnergy < card->cost) {
        printf("能量不足！需要%d能量，当前只有%d能量\n", card->cost, state->playerEnergy);
        return;
    }
    switch (card->type) {
        case CARD_STRIKE: {
            if (card->upgraded) {
                attributed_strike(&state->player, target, 9);
            }
            else {
                attributed_strike(&state->player, target, 6);
            }
        } break;
        case CARD_BASH: {
            if (card->upgraded) {
                attributed_strike(&state->player, target, 10);
                buff_cast(target, VUL, 3);
            }
            else {
                attributed_strike(&state->player, target, 8);
                buff_cast(target, VUL, 2);
            }
        } break;
        case CARD_ANGER: {
            if (card->upgraded) {
                attributed_strike(&state->player, target, 8);
            }
            else {
                attributed_strike(&state->player, target, 6);
            }
            copy_card(&state->discard[state->discard_size++],card);
        } break;
        case CARD_HEADBUTT: {
            if (card->upgraded) {
                attributed_strike(&state->player, target, 12);
            }
            else {
                attributed_strike(&state->player, target, 9);
            }
            int choose_card_temp;
            if (state->discard_size > 0){
                printf("选择弃牌堆中的牌(0-%d):",state->discard_size-1);
                scanf("%d",&choose_card_temp);
                copy_card(&state->pile[state->pile_size++],&state->discard[choose_card_temp]);
                for (int k=choose_card_temp;k<state->discard_size-2;k++) {
                    copy_card(&state->discard[k],&state->discard[k+1]);
                }
                state->discard_size--;
            }
            else
                printf("弃牌堆为空，无法再抽一张牌");
        } break;
        case CARD_HEAVYBLADE: {
            if (card->upgraded) {
                attributed_strike(&game_state.player, target, 14+5*game_state.player.buff[STR]);
            }
            else {
                attributed_strike(&game_state.player, target, 14+3*game_state.player.buff[STR]);
            }
        } break;
        case CARD_IRON_WAVE: {
            if (card->upgraded) {
                block(&game_state.player, 7);
                attributed_strike(&game_state.player, target, 7);
            }
            else {
                block(&game_state.player, 5);
                attributed_strike(&game_state.player, target, 5);
            }
        } break;
        case CARD_PFT_STRIKE: {
            int addbase=card->upgraded?3:2;
            int temp_damage=6;
            for (int k=0;k<state->deck_size-1;k++) {
                if (state->deck[k].type==CARD_STRIKE||state->deck[k].type==CARD_PFT_STRIKE||state->deck[k].type==CARD_POM_STRIKE||state->deck[k].type==CARD_TWIN_STRIKE||state->deck[k].type==CARD_WILD_STRIKE) {
                    temp_damage+=addbase;
                }
            }
            attributed_strike(&game_state.player, target, temp_damage);
        } break;
        case CARD_POM_STRIKE: {
            if (card->upgraded) {
                attributed_strike(&game_state.player, target, 10);
                draw_card(state,2);
            }
            else {
                attributed_strike(&game_state.player, target, 9);
                draw_card(state,1);
            }
        } break;
        //飞剑回旋镖的目标需要主函数那边给出，升级后随机4个，否则3个    //修改：主函数定义完结构以后可以直接在这里写了
        case CARD_BOOMERANG: {
            int count=card->upgraded?4:3;
            for (int c=0;c<count;c++) {
                srand((unsigned)time(NULL));
                attributed_strike(&game_state.player, state->enemy[rand()%state->enemy_count], 3);
            }
        } break;
        //这个Thunderclap是对全体敌人的
        case CARD_THUNDERCLAP: {
            const int dmg=card->upgraded?7:4;
            for (int c=0; c<state->enemy_count; c++) {
                attributed_strike(&state->player, state->enemy[c], dmg);
                buff_cast(state->enemy[c], VUL, 1);
            }
        } break;
        case CARD_TWIN_STRIKE: {
            for (int i=0;i<2;i++) {
                if (card->upgraded) {
                    attributed_strike(&game_state.player, target, 7);
                }
                else{
                    attributed_strike(&game_state.player, target, 5);
                }
            }
        } break;
        case CARD_WILD_STRIKE: {
            time_t t;
            srand((unsigned)time(&t));
            if (card->upgraded) {
                attributed_strike(&game_state.player, target, 17);
            }
            else {
                attributed_strike(&game_state.player, target, 12);
            }
            insert_card(STATE_WOUND,state->pile,&state->pile_size, (state->pile_size>0 ? rand()%state->pile_size : 0),0,1);
        } break;
        case CARD_BODYSLAM: {
            attributed_strike(&game_state.player, target, game_state.player.block);
        } break;
        //clash只有在手牌中都是攻击牌时才能打出
        case CARD_CLASH: {
            if (card->upgraded) {
                attributed_strike(&game_state.player, target, 18);
            }
            else {
                attributed_strike(&game_state.player, target, 14);
            }
        } break;
        //cleave作用于所有敌人
        case CARD_CLEAVE: {
            int dmg=card->upgraded?11:7;
            for (int c=0; c<state->enemy_count; c++) {
                attributed_strike(&state->player, state->enemy[c], dmg);
            }
        } break;
        case CARD_CLOTHESLINE:{
            if (card->upgraded) {
                attributed_strike(&game_state.player, target, 14);
                buff_cast(target, WEK, 3);
            }
            else {
                attributed_strike(&game_state.player, target, 12);
                buff_cast(target, WEK, 2);
            }
        } break;

        case CARD_DROPKICK: {
            if (card->upgraded) {
                attributed_strike(&game_state.player, target, 8);
            }
            else {
                attributed_strike(&game_state.player, target, 5);
            }
            if (target->buff[VUL]) {
                game_state.playerEnergy++;
                draw_card(state,1);
            }
        } break;
        case CARD_HEMOKINESIS: {
            game_state.player.hp-=2;
            if (card->upgraded) {
                attributed_strike(&game_state.player, target, 20);
            }
            else {
                attributed_strike(&game_state.player, target, 15);
            }
        } break;
        case CARD_PUMMEL: {
            int hit_count=card->upgraded?5:4;
            for (int k=0;k<hit_count;k++) {
                attributed_strike(&game_state.player, target, 2);
            }
        } break;
        case CARD_RAMPAGE: {
            attributed_strike(&game_state.player, target, 8);
            if (card->upgraded) {
                card->rampage_extra_dmg+=8;
            }
            else {
                card->rampage_extra_dmg+=5;
            }
        } break;
        case CARD_CHARGE: {
            if (card->upgraded) {
                attributed_strike(&game_state.player, target, 10);
            }
            else {
                attributed_strike(&game_state.player, target, 7);
            }
            insert_card(STATE_DAZED,state->pile,&state->pile_size, (state->pile_size>0 ? rand()%state->pile_size : 0),0,1);
        } break;
        case CARD_SEARING_BLOW: {
            attributed_strike(&game_state.player, target, 12+card->upgraded*(card->upgraded+7)/2);
        } break;
        case CARD_SEVER_SOUL: {
            if (card->upgraded) {
                attributed_strike(&game_state.player, target, 22);
            }
            else {
                attributed_strike(&game_state.player, target, 16);
            }
            int burn_current=0;
            while (burn_current<state->hand_size) {
                if (state->hand[burn_current].type>31) {
                    burn_card(state,burn_current);
                }
                else {
                    burn_current++;
                }
            }
        } break;
        case CARD_UPPERCUT: {
            attributed_strike(&game_state.player, target, 13);
            if (card->upgraded) {
                buff_cast(target, WEK, 2);
                buff_cast(target, VUL, 2);
            }
            else {
                buff_cast(target, WEK, 1);
                buff_cast(target, VUL, 1);
            }
        } break;
        case CARD_BLOOD4: {
            if (card->upgraded) {
                attributed_strike(&game_state.player, target, 22);
            }
            else {
                attributed_strike(&game_state.player, target, 18);
            }
        } break;
        case CARD_WHIRLWIND: {
            for (int k=0;k<game_state.playerEnergy;k++) {
                if (card->upgraded) {
                    attributed_strike(&game_state.player, target, 8);
                }
                else {
                    attributed_strike(&game_state.player, target, 5);
                }
            }
        } break;
        //carnage是虚无牌，当留在手牌未打出时，回合结束进入graveyard
        case CARD_CARNAGE: {
            if (card->upgraded) {
                attributed_strike(&game_state.player, target, 28);
            }
            else {
                attributed_strike(&game_state.player, target, 20);
            }
        } break;
        //feed是消耗牌，需要main那边丢到graveyard而不是discard里
        case CARD_FEED: {
            if (card->upgraded) {
                attributed_strike(&game_state.player, target, 12);
                if (target->hp==0) {
                    game_state.player.max_hp+=4;
                    game_state.player.hp+=4;
                }
            }
            else {
                attributed_strike(&game_state.player, target, 10);
                if (target->hp==0) {
                    game_state.player.max_hp+=3;
                    game_state.player.hp+=3;
                }
            }
        } break;
        case CARD_FIEND_FIRE: {
            int dmg_base=card->upgraded?10:7;
            attributed_strike(&game_state.player, target, (state->hand_size-1)*dmg_base);
            while (state->hand_size>0) {
                burn_card(state,state->hand_size-1);
                //编译器“hand_size不修改大小”的警告不用管。
                //实际上，如果你去看burn_card函数，会发现它一定减小hand_size的值
            }
        } break;
        //immolate作用于所有敌人，需要main func那边重复execute，但是只放一张STATE_BURN到抽牌堆
        case CARD_IMMOLATE: {
            int dmg=card->upgraded?28:21;
            for (int c=0; c<state->enemy_count; c++) {
                attributed_strike(&state->player, state->enemy[c], dmg);
            }
            srand((unsigned)time(NULL));
            insert_card(STATE_BURN, state->pile, &state->hand_size, rand()%state->hand_size, 0, 1);
        } break;
        case CARD_REAPER: {
            int former_hp=target->hp;
            if (card->upgraded){
                attributed_strike(&game_state.player, target, 5);
            }
            else {
                attributed_strike(&game_state.player, target, 4);
            }
            game_state.player.hp+=former_hp-target->hp;
        } break;
        case CARD_BLUDGEON: {
            if (card->upgraded) {
                attributed_strike(&game_state.player, target, 42);
            }
            else {
                attributed_strike(&game_state.player, target, 32);
            }
        } break;
        case CARD_BLOCK: {
            if (card->upgraded) {
                block(&game_state.player, 7);
            }
            else {
                block(&game_state.player, 5);
            }
        } break;
    }
    // 消耗能量     //我把它放到这里了，因为有些卡牌的效果和打出时的能量有关系
    if (card->cost==-1) {   //若打出的卡牌耗能为X（消耗所有能量），则将能量值设为0
        game_state.playerEnergy=0;
    }
    else {
        state->playerEnergy -= card->cost;
    }
}