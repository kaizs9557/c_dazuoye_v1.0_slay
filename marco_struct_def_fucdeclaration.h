#ifndef CDAZUOYE_MARCO_STRUCT_DEF_FUCDECLAARATION_H
#define CDAZUOYE_MARCO_STRUCT_DEF_FUCDECLAARATION_H

#include <stdbool.h>          //支持布尔类型
#include <stdio.h>
#define MAX_ENEMY_COUNT 3//最大敌人数量，为了后面好写，可修改
//buff id
#define STR 0   //力量
#define AGI 1   //敏捷
#define WEK 2   //虚弱
#define BRK 3   //碎甲
#define VUL 4   //易伤
#define NET 5   //织网
#define HMI 6   //人工制品
#define RTE 7   //仪式
#define FNT 8   //击晕
#define THO 9   //荆棘

//行动类型
typedef enum {       //敌人动作行为
    GREAT_ALLIGATOR_ACTION_THump,//重击
    GREAT_ALLIGATOR_ACTION_SHIELD_BASH,//盾击
    GREAT_ALLIGATOR_ACTION_SHOUT,//怒吼//以上行为为大鳄虫行为
    LITTLE_SLIME_ACTION_STAB_ATACK,//史莱姆刺击
    LITTLE_SLIME_ACTION_ATTACK,//史莱姆攻击
    ELITE_MONSTER_LEGAVELIN_ACTION_THUMP,//乐加维林重击
    ELITE_MONSTER_LEGAVELIN_ACTION_SOUL_EXTRACTION,//乐加维林灵魂抽取
    LEGAVELIN_SLEEP,//乐加维林沉睡
    ACTION_MAX,
} ActionType;
typedef enum {
    GREAT_ALLIGATOR,//大锷虫。
    LITTLE_SLIME,//小史莱姆，多体出现
    ELITE_MONSTER_LEGAVELIN,//精英怪乐加维林
    ENEMY_MAX,
}ENERMYTYPE;
//卡牌类型枚举
typedef enum {
    CARD_STRIKE = 0,
    CARD_BASH,
    CARD_ANGER,
    CARD_HEADBUTT,
    CARD_HEAVYBLADE,
    CARD_IRON_WAVE,
    CARD_PFT_STRIKE,
    CARD_POM_STRIKE,
    CARD_BOOMERANG,
    CARD_THUNDERCLAP,
    CARD_TWIN_STRIKE,
    CARD_WILD_STRIKE,
    CARD_BODYSLAM,
    CARD_CLASH,
    CARD_CLEAVE,
    CARD_CLOTHESLINE,

    CARD_DROPKICK,
    CARD_HEMOKINESIS,
    CARD_PUMMEL,
    CARD_RAMPAGE,
    CARD_CHARGE,
    CARD_SEARING_BLOW,
    CARD_SEVER_SOUL,
    CARD_UPPERCUT,
    CARD_BLOOD4,
    CARD_WHIRLWIND,
    CARD_CARNAGE,

    CARD_FEED,
    CARD_FIEND_FIRE,
    CARD_IMMOLATE,
    CARD_REAPER,
    CARD_BLUDGEON,

    CARD_BLOCK,

    CARD_ARMAMENTS,
    CARD_FLEX,
    CARD_HAVOC,
    CARD_SHRUG,
    CARD_GRIT,
    CARD_WARCRY,

    CARD_DISARM,
    CARD_DUAL_WIELD,
    CARD_ENTRENCH,
    CARD_FLAME_BARRIER,
    CARD_GHOSTLY_ARMOR,
    CARD_INFERNAL_BLADE,
    CARD_INTIMIDATE,
    CARD_POWER_THROUGH,
    CARD_RAGE,
    CARD_BATTLE_TRANCE,
    CARD_SECOND_WIND,
    CARD_SEEING_RED,
    CARD_SENTINEL,
    CARD_SHOCKWAVE,
    CARD_SPOT_WEAKNESS,
    CARD_BLOODLETTING,
    CARD_BURNING_PACT,

    CARD_DOUBLE_TAP,
    CARD_EXHUME,
    CARD_IMPERVIOUS,
    CARD_LIMIT_BREAK,
    CARD_OFFERING,

    CARD_EVOLVE,
    CARD_FEEL_NO_PAIN,
    CARD_FIRE_BREATHING,
    CARD_INFLAME,
    CARD_METALLICIZE,
    CARD_RUPTURE,
    CARD_COMBUST,
    CARD_DARK_EMBRACE,

    CARD_DEMON_FORM,
    CARD_JUGGERNAUT,
    CARD_BARRICADE,
    CARD_BERSERK,
    CARD_BRUTALITY,
    CARD_CORRUPTION,

    STATE_WOUND,
    STATE_SLIMED,
    STATE_VOID,
    STATE_BURN,
    STATE_DAZED,
}CARD_TYPES;

//定义药水类型
typedef enum {
    POTION_ATTACK,
    POTION_WEAKEN,
    POTION_BOOM,
    POTION_VUL,
    POTION_DEXTERITY,
    POTION_BLOCK,
    POTION_BLOOD,
    POTION_FIRE,
}POTION_TYPES;

//定义entity结构，玩家与怪物共用//修正在新的版本种怪物和玩家entity不能公用
typedef struct entity {
    int max_hp;
    int hp;
    int block;
    int buff[10];
    int strength;
    bool recently_hurt;
} ENTITY;
//定义遗物类型
typedef enum {
    RELIC_NONE, //常驻效果
    RELIC_STRENGTH_BAND, //力量手环 战斗开始获得2点力量
    RELIC_IRON_ARMOR, //铁质盔甲 战斗开始获得3点盔甲
    RELIC_DRAGGER, //锋利匕首 战斗开始获得1点力量（力量手环阉割版）
    RELIC_LUCKY_COIN, //幸运金币 回合结束后额外获得3金币（待后期完善）
    RELIC_COST_BATTERY, //能量电池 每回合能量值+1
    RELIC_REBOUND_NECKLACE, //反击项链 受到伤害时，反弹所受伤害的10%
    RELIC_INITIAL_PENDANT, //起始手牌吊坠 每场战斗第一回合多抽一张牌
    RELIC_BURNING_BLOOD, //燃烧之血 整场战斗结束时回复6点生命
    RELIC_STRANGE_DONUT, //奇异甜圈圈 最大生命值提升
}RELIC_TYPES;
//定义玩家拥有的遗物结构体
typedef struct relic_status {
    bool hasStrengthBand; //力量手环
    bool hasIronArmor; //铁质盔甲
    bool hasDragger; //锋利匕首
    bool hasLuckyCoin; //幸运金币
    bool hasCostBattery; //能量电池
    bool hasReboundNecklace; //反击项链
    bool hasInitialPendant; //起始手牌吊坠
    bool hasBurningBlood; //燃烧之血
    bool hasStrangeDonut; //奇异甜圈圈

    int relicCount; // 持有遗物总数
} RELIC_STATUS;
//定义card结构，包括一个类型与标记是否升级的整型数，以及打出它需要的cost
//不用bool是因为灼热攻击可以多次升级
typedef struct card {
    int upgraded;
    CARD_TYPES type;
    int cost;
    int rampage_extra_dmg;
} CARD;

// 定义游戏状态结构体
typedef struct gamestate {
    ENTITY player; //战局内基本信息
    ENTITY*enemy[MAX_ENEMY_COUNT];//把敌人改成数组指针，方便调用多个敌人
    RELIC_STATUS relics;

    bool isInCombat;  //游戏总基本信息
    int combatTurn;  //回合数
    int currentFloor;
    int playerEnergy;
    int playerMaxEnergy;
    int playerGold;
    int cardsPlayedThisTurn;

    //卡牌基本信息
    //定义牌组(deck)，抽牌堆(pile)，手牌(hand)，弃牌堆(discard)，以及被消耗牌堆(graveyard)
    CARD lib[40];
    CARD deck[40];   //100指牌组最多数量
    CARD pile[40];
    CARD hand[12];    //12指最多手牌数量
    CARD discard[40];
    CARD graveyard[40];
    int lib_size;
    int deck_size;
    int pile_size;
    int hand_size;
    int discard_size;
    int graveyard_size;
    int enemy_count;//定义敌人数量
} GAME_STATE;

extern GAME_STATE game_state;//声明一个全局游戏环境 因为在多个文件中都用了game_state，所以要用extern声明

typedef struct level{
    int level_number;//关卡在地图上的编号
    const char* level_name;//关卡名称
    ENERMYTYPE enemy_types[MAX_ENEMY_COUNT];//修改为结构类型//数组中有几个数就代表每局有几个敌人
    int total_count;                   //关卡中敌人总数量
    int reward;                               //方便后面设计奖励
}Levelconfig;          //关卡配置管理系统，之后配置的人和奖励的时候就用这个
Levelconfig* create_level(int level_number);//创建关卡配置
bool if_victory(GAME_STATE* state, Levelconfig* level);//判断胜利与否的函数

//定义卡牌cost
typedef enum {
    COST_STRIKE = 1,
    COST_BASH = 2,
    COST_ANGER = 0,
    COST_HEADBUTT = 1,
    COST_HEAVYBLADE = 2,
    COST_IRON_WAVE = 1,
    COST_PFT_STRIKE = 2,
    COST_POM_STRIKE = 1,
    COST_BOOMERANG = 1,
    COST_THUNDERCLAP = 1,
    COST_TWIN_STRIKE = 1,
    COST_WILD_STRIKE = 1,
    COST_BODYSLAM = 1,
    COST_CLASH = 0,
    COST_CLEAVE = 1,
    COST_CLOTHESLINE = 2,
    //后面我加上去了
    COST_DROPKICK = 1,
    COST_HEMOKINESIS = 1,
    COST_PUMMEL = 1,
    COST_RAMPAGE = 1,
    COST_CHARGE = 1,
    COST_SEARING_BLOW = 2,
    COST_SEVER_SOUL = 2,
    COST_UPPERCUT = 2,
    COST_BLOOD4 = 3,
    COST_WHIRLWIND = -1,
    COST_CARNAGE = 2,

    COST_FEED = 1,
    COST_FIEND_FIRE = 2,
    COST_IMMOLATE = 2,
    COST_REAPER = 2,
    COST_BLUDGEON = 3,

    COST_BLOCK = 1,

    COST_ARMAMENTS = 1,
    COST_FLEX = 0,
    COST_HAVOC = 1,
    COST_SHRUG = 2,
    COST_GRIT = 1,
    COST_WARCRY = 0,

    COST_DISARM = 1,
    COST_DUAL_WIELD = 1,
    COST_ENTRENCH = 1,
    COST_FLAME_BARRIER = 2,
    COST_GHOSTLY_ARMOR = 1,
    COST_INFERNAL_BLADE = 1,
    COST_INTIMIDATE = 0,
    COST_POWER_THROUGH = 0,
    COST_RAGE = 1,
    COST_BATTLE_TRANCE = 1,
    COST_SECOND_WIND = 1,
    COST_SEEING_RED = 1,
    COST_SENTINEL = 1,
    COST_SHOCKWAVE = 2,
    COST_SPOT_WEAKNESS = 1,
    COST_BLOODLETTING = 2,
    COST_BURNING_PACT = 0,

    COST_DOUBLE_TAP = 1,
    COST_EXHUME = 1,
    COST_IMPERVIOUS = 2,
    COST_LIMIT_BREAK = 1,
    COST_OFFERING = 0,

    COST_EVOLVE = 2,
    COST_FEEL_NO_PAIN = 2,
    COST_FIRE_BREATHING = 2,
    COST_INFLAME = 2,
    COST_METALLICIZE = 2,
    COST_RUPTURE = 1,
    COST_COMBUST = 1,
    COST_DARK_EMBRACE = 2,

    COST_DEMON_FORM = 3,
    COST_JUGGERNAUT = 2,
    COST_BARRICADE = 3,
    COST_BERSERK = 0,
    COST_BRUTALITY = 1,
    COST_CORRUPTION = 3,

    COST_WOUND = 1,
    COST_SLIMED = 1,
    COST_VOID = 1,
    COST_BURN = 1,
    COST_DAZED = 1,
} CARD_COST;

typedef void (*ActionExecuteFunc)(ENTITY* player, ENTITY* enemy);
typedef float (*ActionCalculateUtilityFunc)(ENTITY* player, ENTITY* enemy, int bout);
typedef struct {
    ActionType type;
    const char* name;
    ActionCalculateUtilityFunc calculate_utility;
    ActionExecuteFunc execute;
} ENERMYAction;
typedef struct {
    ENERMYTYPE type;
    ENERMYAction* actions[ACTION_MAX];
    ActionType current_action;
    int high_action_count;
    int low_action_count;
} ENERMYEntity;

// 卡牌函数声明
void copy_card(CARD* dest, CARD* source);
void random_permutation(int i, int j, int order[]);
void shuffle(GAME_STATE* state);
int draw_card(GAME_STATE* state, int draw_count);
void burn_card(GAME_STATE* state, int i);
void discard_card(GAME_STATE* state, CARD card_array[], int* array_size, int i);
void insert_card(CARD_TYPES type, CARD card_array[], int* array_size, int i, int upgraded, int cost);
int unattributed_strike(ENTITY* target, int damage);
int attributed_strike(ENTITY* caster, ENTITY* target, int damage);
void block(ENTITY* caster, int defence);
void buff_cast(ENTITY* target, int buff_id, int count);
void execute_cards(GAME_STATE* state, ENTITY* target, CARD* card);
int get_card_type(CARD_TYPES type);
const char* get_card_name(CARD_TYPES card_type);

// 遗物函数声明
void acquireRelic(const char* relicName, GAME_STATE* state);
void displayRelics(RELIC_STATUS* relics);
void relic_StrengthBand(GAME_STATE* state);
void relic_IronArmor(GAME_STATE* state);
int relic_Dragger(int baseDamage, GAME_STATE* state);
void relic_LuckyCoin(GAME_STATE* state);
void relic_CostBattery(GAME_STATE* state);
int relic_ReboundNecklace(int damageReceived, GAME_STATE* state,ENTITY* enemy);
int relic_InitialPendant(int baseDrawCount, GAME_STATE* state);
void relic_BurningBlood(GAME_STATE* state);
void relic_StrangeDonut(GAME_STATE* state);
void apply_start_of_combat_relics(GAME_STATE* state);
void select_random_relic(GAME_STATE* state);
ENERMYEntity* create_ai_entity(int flag);
void destroy_ai_entity(ENERMYEntity* entity);
void ai_think(ENERMYEntity* entity, ENTITY* player, ENTITY* enemy, int bout);
void ai_execute_best_action(ENERMYEntity* entity, ENTITY* player, ENTITY* enemy);
void initialize_all_actions(ENERMYEntity* entity);

// 初始化函数
// 初始化函数
void initialize_game_state(GAME_STATE* state, Levelconfig* level);

/* --- 数学工具 --- */
float clamp(float value, float min, float max);
float lerp(float a, float b, float t);
float inverse_lerp(float value, float min, float max);
float bout_utility(float bout, float optimal_range, float max_range);

//日志函数
void wlog(FILE* log, const char* format, ...);

//药水函数
void potion(GAME_STATE* state, POTION_TYPES type);
#endif