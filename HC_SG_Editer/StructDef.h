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
	CString status;   //״̬
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
	char type[2];    //ò�������Ļ��ǻ����˼��ֻ������1 �� 0��ֵ
	char Name[16];		// ����
	char A1[3]; // ��ֵ���ǲ�֪����ʲô
	unsigned __int16 Level;
	unsigned __int32 Hp;
	unsigned __int32 Exp;
	char A2[16]; // ��ֵ���ǲ�֪����ʲô
	unsigned __int16 Attr_str; //����
	unsigned __int16 Attr_int;//����
	unsigned __int16 Type;//����
	unsigned __int16 Attr_dex;//����
	unsigned __int16 Attr_mind; //��Ӧ
	
	char A3[58]; // ��ֵ���ǲ�֪����ʲô
	unsigned __int8 Loyal; //�ҳ�
	char A4[3]; // ��ֵ���ǲ�֪����ʲô
	unsigned __int8 Attack;//����������
	unsigned __int8 Defence;//����������
	char A5[22]; // ��ֵ
};
#pragma pack()

#pragma pack(1)
struct AccSkills
{
	char SkillsUsing[551];    // ����ʹ�ü������ܣ������Ŷ�Ӧ����ID
	char SkillsHad[551];      // ѧ�����ܹ����ټ����ܣ������Ŷ�Ӧ����ID
};
#pragma pack() 


#pragma pack(1)
struct AccAttr
{
	char Account[24];  // �����ʺ�
	char A1[4];
	unsigned __int32 nIndex;	// ���
	char Name[15];		// ����
	char Corps[15];		//����
	unsigned __int32 Gold;		//��Ǯ
	unsigned __int32 Exp;
	unsigned __int16 SkillExp;
	unsigned __int16 Anger;
	unsigned __int16 AngerNum;
	unsigned __int16 Level;
	char A2[7];
	unsigned __int16 Attr_Num;  //���Ե�
	unsigned __int32 Honor;	//��ѫֵ
	unsigned __int32 Hp;
	unsigned __int32 Mp;

	char A3[249];

	unsigned __int16 Attr_str_up;   // ��������
	unsigned __int16 Attr_int_up;
	unsigned __int16 Attr_con_up;
	unsigned __int16 Attr_dex_up;
	unsigned __int16 Attr_mind_up;
	unsigned __int16 Attr_leader_up;

	unsigned __int16 Attr_str; //����
	unsigned __int16 Attr_int;//����
	unsigned __int16 Attr_con;//����	
	unsigned __int16 Attr_dex;//����
	unsigned __int16 Attr_mind; //��Ӧ	
	unsigned __int16 Attr_leader;//ͳ��

	char A4[979];

	unsigned __int8 PackNum;//��������		
	unsigned __int8 StoreNum; //�ֿ����

	char A5[169];

	unsigned __int16 Officer;	//��ְ

	char A6[232];
};
#pragma pack() 

#pragma pack(1)
struct OrganizeAttr
{
	char A1[2312]; // ��ֵ
	char A2[8]; // ��ֵ����;δ֪
	char A3[6]; // ��ֵ
	unsigned __int16  StageId; // ���д���
	char A4[4]; // ��ֵ����;δ֪
	char OrganizeLeader[15]; // ���ų�
	char A5[4]; // ��ֵ����;δ֪
	char A6[8]; // ��ֵ����;δ֪

	char A7[1473]; // ��ֵ
	char A8[2]; // ��ֵ����;δ֪
	char A9[7]; //��ֵ
	char OrganizeName[15]; //������
	char OrganizeLeaderZh[15]; //�ų�
	char OrganizeLeaderFu[15]; //����
	char A10[2]; //�²�Ϊ��Ա����
	char A11[9]; // ��ֵ����;δ֪

	char A12[519]; // ��ֵ
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
	CString Name;	// ��ɫ��
	CString Level;	// �ȼ�
	CString Job;	// ְҵ
	CString Nationality;	// ����
	CString Honor;	// ��ѫֵ
	CString Kills;	// �ֵ���
	CString Corps;
};
#pragma pack() 

#pragma pack(1)
struct CwarCorps
{
	char Name[15];	// ������
	char ID[15];	// Ψһ��ʶ
	unsigned __int16 Honor;	// ��ѫ��
};
#pragma pack() 

#pragma pack(1)
struct HistoryCbHeroes
{
	CString Account;	// ��ɫ�ʺ�
	CString Name;	// ��ɫ��
	CString Job;	// ְҵ
	CString Nationality;	// ����
	CString Points;	// ����
	CString Honor;	// ��ѫֵ
	CString Kills;	// �ֵ���
};
#pragma pack() 

#pragma pack(1)
struct ServerConfigTime
{
	CString Period;  // ����ʱ��
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
	CString OrganizeName;  // ������
	CString OrganizeNameOfLeaderZh; //�ų�
	CString OrganizeAccountOfLeaderZh; //�ų��ʺ�
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
	CListCtrl *plist;//���ڴ洢�б�ؼ���ָ��  
	int col;//���ڴ洢Ҫ�������е����  
};//�ص�����������������Ӧ�����ݽṹ�������Զ��壬����Ҫ����������  