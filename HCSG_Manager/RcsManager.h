#pragma once
#include "afxwin.h"
#include "SQLite3Helper.h"
#include "xTreeTest.h"
#include "RBTree.h"
#include "IndexList.h"
#include "StructDef.h"

//#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

struct CRcsFile
{
	CString m_csFileName;
	CString m_csModTimeStamp;
};

#define RCS_TPYE_DEF 0		// 物品等资源定义文件
#define RCS_TYPE_DATA 1		// 游戏保存的游戏资源，角色，装备，属性等，主要是更新进数据方便查询
#define RCS_TYPE_INI 2		// 配置文件，比如战场、国战的配置和排名文件

#define CONFIG_FILE_PATH ".\\Profile\\"
// server folder\\DataBase\\saves
// server folder\\login

struct CRcsFilesDefine
{
	int m_iFileType;
	CString m_csFileName;	// 只包含名字，路径要根据文件类型来添加
	int(*update)(CRcsFile * pCRcsFile);			// 设置更新该文件所对应数据可以的函数
};


struct CKeys
{
	int m_iOffset;						// 作为索引键值的成员字段相对于结构体起始位置的偏移
	int(*compare)(void * a, void * b);	// 比较函数，参数类型需要在具体的实现中进行强转
};

//数据库更新回调接口
int UpdateItems(CRcsFile * pCRcsFile);
int UpdateStageInfo(CRcsFile * pCRcsFile);
int UpdatePlayersInfo(CRcsFile * pCRcsFile);

class CRcsManager
{
public:
	CRcsManager();
	virtual ~CRcsManager();

	bool RcsFileIsLatest(CRcsFile * pCRcsFile);
	int UpdateRcsFileTimeStamp(CRcsFile * pCRcsFile);

	// 游戏道具物品操作
// 	struct ItemDef* ReadItemById(CString sItemId);
// 	struct ItemDef* ReadItemByName(CString sItemName);
	int WriteItem(int iToken, struct ItemDef* pItemDef);
	int WriteStage(int iToken, struct StageDef* pStageDef);
	int InsetPlayerInfo(int iToken, struct AccAttr cAccAtrr);

	// 检查各种文件的修改时间，如果文件的修改时间比数据库的时间更新，则更新数据库
	int SyncSQLite3db();

	// 资源查找


private:
	CSqlite3Helper m_CSqliteHelper;
	CRBTree<struct AccAttr, char*> *m_pRBTreePlayerInfo = NULL;
	CIndexList<struct AccAttr, struct CKeys> *m_pIndexListPlayerInfo = NULL;
};