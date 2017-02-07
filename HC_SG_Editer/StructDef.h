#pragma once
#include "afxwin.h"

#pragma pack(1)
struct GameAcc{
	CString account;
	CString password;
	CString password2;
	CString duedate;
	CString enable;
	CString lock_duedate;
	CString logout_time;
	CString ip;
	CString create_time;
	CString privilege;
	CString status;   //状态
	CString sec_pwd;
	CString first_ip;
	CString point;
	CString trade_psw;
	CString IsAdult;
	CString OnlineTime;
	CString OfflineTime;
	CString LastLoginTime;
	CString LastLogoutTime;
};
#pragma pack() 

#pragma pack(1)
struct SoldierAttr
{
	char type[2];    //貌似是死的还是活的意思，只看到了1 和 0的值
	char Name[16];		// 名称
	char A1[3]; // 有值但是不知道是什么
	unsigned __int16 Level;
	unsigned __int32 Hp;
	unsigned __int32 Exp;
	char A2[16]; // 有值但是不知道是什么
	unsigned __int16 Attr_str; //武力
	unsigned __int16 Attr_int;//智力
	unsigned __int16 Type;//兵种
	unsigned __int16 Attr_dex;//体魄
	unsigned __int16 Attr_mind; //反应
	
	char A3[58]; // 有值但是不知道是什么
	unsigned __int8 Loyal; //忠诚
	char A4[3]; // 有值但是不知道是什么
	unsigned __int8 Attack;//附属攻击力
	unsigned __int8 Defence;//附属防御力
	char A5[22]; // 空值
};
#pragma pack()

#pragma pack(1)
struct AccSkills
{
	char SkillsUsing[551];    // 正在使用几级技能，数组编号对应技能ID
	char SkillsHad[551];      // 学到了总共多少级技能，数组编号对应技能ID
};
#pragma pack() 


#pragma pack(1)
struct AccAttr
{
	char Account[24];  // 任务帐号
	char A1[4];
	unsigned __int32 nIndex;	// 序号
	char Name[15];		// 名称
	char Corps[15];		//军团
	unsigned __int32 Gold;		//金钱
	unsigned __int32 Exp;
	unsigned __int16 SkillExp;
	unsigned __int16 Anger;
	unsigned __int16 AngerNum;
	unsigned __int16 Level;
	char A2[7];
	unsigned __int16 Attr_Num;  //属性点
	unsigned __int32 Honor;	//功勋值
	unsigned __int32 Hp;
	unsigned __int32 Mp;

	char A3[249];

	unsigned __int16 Attr_str_up;   // 属性上限
	unsigned __int16 Attr_int_up;
	unsigned __int16 Attr_con_up;
	unsigned __int16 Attr_dex_up;
	unsigned __int16 Attr_mind_up;
	unsigned __int16 Attr_leader_up;

	unsigned __int16 Attr_str; //武力
	unsigned __int16 Attr_int;//智力
	unsigned __int16 Attr_con;//精神	
	unsigned __int16 Attr_dex;//体魄
	unsigned __int16 Attr_mind; //反应	
	unsigned __int16 Attr_leader;//统御

	char A4[979];

	unsigned __int8 PackNum;//背包格数		
	unsigned __int8 StoreNum; //仓库格数

	char A5[169];

	unsigned __int16 Officer;	//官职

	char A6[232];
};
#pragma pack() 

#pragma pack(1)
struct OrganizeAttr
{
	char A1[2312]; // 空值
	char A2[8]; // 有值，用途未知
	char A3[6]; // 空值
	unsigned __int16  StageId; // 城市代码
	char A4[4]; // 有值，用途未知
	char OrganizeLeader[15]; // 军团长
	char A5[4]; // 有值，用途未知
	char A6[8]; // 有值，用途未知

	char A7[1473]; // 空值
	char A8[2]; // 有值，用途未知
	char A9[7]; //空值
	char OrganizeName[15]; //军团名
	char OrganizeLeaderZh[15]; //团长
	char OrganizeLeaderFu[15]; //副团
	char A10[2]; //猜测为团员数量
	char A11[9]; // 有值，用途未知

	char A12[519]; // 空值
};
#pragma pack()

#pragma pack(1)
struct ItemDef{
	CString ID;
	CString Name;
};
#pragma pack() 

#pragma pack(1)
struct StageDef{
	CString ID;
	CString Name;
};
#pragma pack() 

#pragma pack(1)
struct ArmyNameDef{
	CString ID;
	CString Name;
};
#pragma pack()

#pragma pack(1)
struct ArmyDef{
	CString Code;
	CString Name;
	CString reborn_delay;
	CString reborn_range;
	CString disappear_time;
	CString list;
	CString map_list;
	CString mission_boss;
};
#pragma pack() 

#pragma pack(1)
struct CwarHeroes
{
	CString Name;	// 角色名
	CString Level;	// 等级
	CString Job;	// 职业
	CString Nationality;	// 国籍
	CString Honor;	// 功勋值
	CString Kills;	// 讨敌数
	CString Corps;
};
#pragma pack() 

#pragma pack(1)
struct CwarCorps
{
	char Name[15];	// 军团名
	char ID[15];	// 唯一标识
	unsigned __int16 Honor;	// 功勋和
};
#pragma pack() 

#pragma pack(1)
struct HistoryCbHeroes
{
	CString Account;	// 角色帐号
	CString Name;	// 角色名
	CString Job;	// 职业
	CString Nationality;	// 国籍
	CString Points;	// 积分
	CString Honor;	// 功勋值
	CString Kills;	// 讨敌数
};
#pragma pack() 

#pragma pack(1)
struct ServerConfigTime
{
	CString Period;  // 持续时间
	CStringArray ModStartTimes;
	CStringArray TuseStartTimes;
	CStringArray WedStartTimes;
	CStringArray ThursStartTimes;
	CStringArray FriStartTimes;
	CStringArray SatStartTimes;
	CStringArray SunStartTimes;
};
#pragma pack()

#pragma pack(1)
struct CwarAwards
{
	CString OrganizeName;  // 军团名
	CString OrganizeNameOfLeaderZh; //团长
	CString OrganizeAccountOfLeaderZh; //团长帐号
	CString StageName;
	CString StageID;
	unsigned int AwardsTimes;
};
#pragma pack()


#pragma pack(1)
struct Players
{
	CString code;
	CString name;
	CString level;
	CString wid;
	CString size;
	CString Class;
	CString exp;
	CString hp;
	CString mp;
	CString attr_str;
	CString attr_int;
	CString attr_mind;
	CString attr_con;
	CString attr_dex;
	CString attr_leader;
	CString walk_speed;
	CString run_speed;
	CString attack_speed;
	CString attack_delay;
	CString cast_attack_delay;
	CString attack_range;
	CString attack_effect_range;
	CString damage;
	CString defense;
	CString magic_attack_type;
	CString ai;
	CString ai_reborn_range;
	CString ai_reborn_delay;
	CString ai_guard_range;
	CString gold;
	CString drop;
	CString sfx_move;
	CString sfx_attack;
	CString sfx_hit;
	CString sfx_hurt;
	CString sfx_dead;
	CString country;
	CString skill_exp;
	CString attr_level;
	CString ratio_hit;
	CString height;
	CString drop_mission;
	CString magic_defense_type;
	CString ai_call_range;
	CString ratio_miss;
	CString ratio_attack_x2;
	CString function;
	CString set_color;
	CString sex;
	CString dead_horse;
	CString zoom;
	CString special_attack;
	CString magic_power;
	CString anti_status;
	CString appear_time;
	CString spc_flag;
	CString call_sol1;
	CString call_sol2;
	CString call_sol3;
	CString call_sol4;
	CString call_sol5;
	CString call_sol_total;
	CString appear_ratio;
	CString no_back_off;
	CString ai_help_self_ratio;
	CString ai_help_self_magic;
	CString ai_help_self_level;
	CString equip_weapon;
	CString equip_horse;
	CString bp;
	CString office;
	CString ai_fast_run_ratio;
	CString ai_fast_run_magic;
	CString ai_fast_run_level;
	CString boss_cast_all;
	CString call_ratio;
	CString hp_low_ratio_attack;
	CString attack_spec_ratio;
	CString cnpc_flag;
	CString armor_bless;
	CString boss_teleport;
	CString equip_shield;
	CString boss_call_all;
	CString use_leader;
	CString cnpc_cell;
	CString talk_no_dir;
	CString boss_soul_item;
};
#pragma pack()

#pragma pack(1)
struct BagsDrop
{
	CString ItemName;  
	CString DropId;
};
#pragma pack()

#pragma pack(1)
struct DropsRange
{
	CString DropId;
	CString DropRange;
};
#pragma pack()

struct DATA  
{  
	CListCtrl *plist;//用于存储列表控件的指针  
	int col;//用于存储要排序主列的序号  
};//回调函数第三个参数对应的数据结构，可以自定义，至少要包含这两项  