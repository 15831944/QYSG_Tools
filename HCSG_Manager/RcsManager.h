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

#define RCS_TPYE_DEF 0		// ��Ʒ����Դ�����ļ�
#define RCS_TYPE_DATA 1		// ��Ϸ�������Ϸ��Դ����ɫ��װ�������Եȣ���Ҫ�Ǹ��½����ݷ����ѯ
#define RCS_TYPE_INI 2		// �����ļ�������ս������ս�����ú������ļ�

#define CONFIG_FILE_PATH ".\\Profile\\"
// server folder\\DataBase\\saves
// server folder\\login

struct CRcsFilesDefine
{
	int m_iFileType;
	CString m_csFileName;	// ֻ�������֣�·��Ҫ�����ļ����������
	int(*update)(CRcsFile * pCRcsFile);			// ���ø��¸��ļ�����Ӧ���ݿ��Եĺ���
};


struct CKeys
{
	int m_iOffset;						// ��Ϊ������ֵ�ĳ�Ա�ֶ�����ڽṹ����ʼλ�õ�ƫ��
	int(*compare)(void * a, void * b);	// �ȽϺ���������������Ҫ�ھ����ʵ���н���ǿת
};

//���ݿ���»ص��ӿ�
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

	// ��Ϸ������Ʒ����
// 	struct ItemDef* ReadItemById(CString sItemId);
// 	struct ItemDef* ReadItemByName(CString sItemName);
	int WriteItem(int iToken, struct ItemDef* pItemDef);
	int WriteStage(int iToken, struct StageDef* pStageDef);
	int InsetPlayerInfo(int iToken, struct AccAttr cAccAtrr);

	// �������ļ����޸�ʱ�䣬����ļ����޸�ʱ������ݿ��ʱ����£���������ݿ�
	int SyncSQLite3db();

	// ��Դ����


private:
	CSqlite3Helper m_CSqliteHelper;
	CRBTree<struct AccAttr, char*> *m_pRBTreePlayerInfo = NULL;
	CIndexList<struct AccAttr, struct CKeys> *m_pIndexListPlayerInfo = NULL;
};