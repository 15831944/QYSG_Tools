#include "stdafx.h"
#include "SQLite3Helper.h"
#include "StructDef.h"
#include "ComString.h"
#include <ctime>

CSqlite3Helper::CSqlite3Helper()
{
}

CSqlite3Helper::~CSqlite3Helper()
{

}

int CSqlite3Helper::Open()
{
	db.open(DB_DEFAULT_NAME);
	InitializeTables();
	TestProfileInterface();
	TestProfileFileInterface();

	return EXIT_SUCCESS;
}

int CSqlite3Helper::Open(char *dbName)
{
	db.open(dbName);
	InitializeTables();

	return EXIT_SUCCESS;
}

void CSqlite3Helper::Close()
{
	db.close();
}

int CSqlite3Helper::InitializeTables()
{
	string sSqlCmd;
	int iRet;

	// 配置参数表
	if (!db.tableExists("profiles"))
	{
		sSqlCmd = "CREATE TABLE profiles ( Id INTEGER PRIMARY KEY AUTOINCREMENT, app_name VARCHAR(128), \
			key VARCHAR(128), value VARCHAR(128) ) ";
		iRet = db.execDML(sSqlCmd.c_str());
		if (iRet != 0)
		{
			return -EXIT_FAILURE;
		}
	}
	

	// 创建文件表,记录修改时间
	if (!db.tableExists("profile_files"))
	{
		sSqlCmd = "CREATE TABLE profile_files ( Id INTEGER PRIMARY KEY AUTOINCREMENT, file_name VARCHAR(128), timestamp DATETIME ) ";
		iRet = db.execDML(sSqlCmd.c_str());
		if (iRet != 0)
		{
			return -EXIT_FAILURE;
		}
	}

	// 创建物品表，对应item.h
	if (!db.tableExists("game_items"))
	{
		sSqlCmd = "CREATE TABLE game_items ( Id INTEGER PRIMARY KEY AUTOINCREMENT, item_id VARCHAR(128), \
				  item_name VARCHAR(128), item_name_zh VARCHAR(128)) ";
		iRet = db.execDML(sSqlCmd.c_str());
		if (iRet != 0)
		{
			return -EXIT_FAILURE;
		}
	}

	// 创建城市表，对应stage.h
	if (!db.tableExists("game_stages"))
	{
		sSqlCmd = "CREATE TABLE game_stages ( Id INTEGER PRIMARY KEY AUTOINCREMENT, stage_id VARCHAR(128), \
				  stage_name VARCHAR(128), stage_name_zh VARCHAR(128)) ";
		iRet = db.execDML(sSqlCmd.c_str());
		if (iRet != 0)
		{
			return -EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}


// 配置参数表操作接口
bool CSqlite3Helper::ExistProfile(string app_name, string key)
{
	string sSqlCmd = "select 1 from profiles where app_name = '" + app_name + "' and key = '" + key + "' ";
	CppSQLite3Query dbQuery = db.execQuery((ASCIIToUTF8(sSqlCmd.c_str())));
	if (!dbQuery.eof())
		return true;

	return false;
}

int CSqlite3Helper::ReadProfileValue(string app_name, string key, string & value)
{
	if (!ExistProfile(app_name, key))
		return EXIT_FAILURE;

	string sSqlCmd = "select * from profiles where app_name = '" + app_name + "' and key = '" + key + "' ";
	CppSQLite3Query dbQuery = db.execQuery(sSqlCmd.c_str());

	if (dbQuery.eof())
		return EXIT_FAILURE;

	value = dbQuery.getStringField("value");

	return EXIT_SUCCESS;
}

int CSqlite3Helper::WriteProfileValue(string app_name, string key, string value)
{
	string sSqlCmd = "";
	int iRet = 0;

	if (!ExistProfile(app_name, key))
	{
		// 键值对不存在则插入新的配置参数
		sSqlCmd = "insert into profiles (app_name,key,value) values ('" + app_name + "','" + key + "','" + value + "')";
		iRet = db.execDML(ASCIIToUTF8(sSqlCmd.c_str()));
		//iRet = db.execDML("insert into profiles (app_name,key,value) values ('服务','地址','三国')");
// 		sSqlCmd = "insert into profiles (app_name,key,value) values ('服务','地址','三国')";
// 		iRet = db.execDML(UnicodeToUtf8(sSqlCmd.c_str()));
		if (iRet == 0)
			return EXIT_FAILURE;
	}
	else
	{
		// 键值对存在则更新配置参数
		sSqlCmd = "update profiles set value = '" + value + "' where app_name = '" + app_name + "' and key = '" + key + "'";
		iRet = db.execDML(sSqlCmd.c_str());
		if (iRet == 0)
			return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void CSqlite3Helper::TestProfileInterface()
{
// 	string value;
// 	WriteProfileValue("G1", "K1", "1");
// 	ReadProfileValue("G1", "K1", value);
// 	TRACE("value:%s\n", value.c_str());
// 
// 	WriteProfileValue("G1", "K2", "2");
// 	ReadProfileValue("G1", "K2", value);
// 	TRACE("value:%s\n", value.c_str());
// 
// 	WriteProfileValue("G2", "K1", "3");
// 	ReadProfileValue("G2", "K1", value);
// 	TRACE("value:%s\n", value.c_str());
// 
// 	WriteProfileValue("G3", "K3", "4");
// 	ReadProfileValue("G3", "K3", value);
// 	TRACE("value:%s\n", value.c_str());
// 
// 	WriteProfileValue("直剑", "K2", "1");
// 	ReadProfileValue("G1", "K2", value);
// 	TRACE("value:%s\n", value.c_str());
}

// 数据文件时间戳记录表操作接口
bool CSqlite3Helper::ExistProfileFile(string file_name)
{
	string sSqlCmd = "select 1 from profile_files where file_name = '" + file_name + "' ";
	CppSQLite3Query dbQuery = db.execQuery((ASCIIToUTF8(sSqlCmd.c_str())));
	if (!dbQuery.eof())
		return true;

	return false;
}

int CSqlite3Helper::ReadProfileFile(string file_name, string & timestamp)
{
	if (!ExistProfileFile(file_name))
		return EXIT_FAILURE;

	string sSqlCmd = "select * from profile_files where file_name = '" + file_name + "' ";
	CppSQLite3Query dbQuery = db.execQuery(sSqlCmd.c_str());

	if (dbQuery.eof())
		return EXIT_FAILURE;

	timestamp = dbQuery.getStringField("timestamp");

	return EXIT_SUCCESS;
}

int CSqlite3Helper::WriteProfileFile(string file_name, string timestamp)
{
	string sSqlCmd = "";
	int iRet = 0;

	if (!ExistProfileFile(file_name))
	{
		// 键值对不存在则插入新的配置参数
		sSqlCmd = "insert into profile_files (file_name,timestamp) values ('" + file_name + "','" + timestamp + "')";
		iRet = db.execDML(ASCIIToUTF8(sSqlCmd.c_str()));
		if (iRet == 0)
			return EXIT_FAILURE;
	}
	else
	{
		// 键值对存在则更新配置参数
		sSqlCmd = "update profile_files set timestamp = '" + timestamp + "' where file_name = '" + file_name + "'";
		iRet = db.execDML(sSqlCmd.c_str());
		if (iRet == 0)
			return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void CSqlite3Helper::TestProfileFileInterface()
{
// 	string value;
// 	time_t rawtime;
// 	struct tm timeinfo;
// 	char buffer[80];
// 
// 	time(&rawtime);
// 	localtime_s(&timeinfo, &rawtime);
// 
// 	strftime(buffer, sizeof(buffer), "%Y-%m-%d %I:%M:%S", &timeinfo);
// 	std::string timestamp(buffer);
// 
// 	WriteProfileFile("F1", timestamp);
// 	ReadProfileFile("F1", value);
// 	TRACE("value:%s\n", value.c_str());
// 
// 	WriteProfileFile("F2", timestamp);
// 	ReadProfileFile("F2", value);
// 	TRACE("value:%s\n", value.c_str());
}

// 物品表操作接口
int CSqlite3Helper::ReadItemByPos(const int pos, string & item_id, string & item_name)
{
	string sSqlCmd = "select * from game_items where Id = '" + Int2STDStr(pos) + "' ";
	CppSQLite3Query dbQuery = db.execQuery(sSqlCmd.c_str());

	if (dbQuery.eof())
		return EXIT_FAILURE;

	item_id = dbQuery.getStringField("item_id");
	item_name = dbQuery.getStringField("item_name");

	return EXIT_SUCCESS;
}

int CSqlite3Helper::ReadItemById(const string item_id, string & item_name)
{
	string sSqlCmd = "select * from game_items where item_id = '" + item_id + "' ";
	CppSQLite3Query dbQuery = db.execQuery(sSqlCmd.c_str());

	if (dbQuery.eof())
		return EXIT_FAILURE;

	item_name = dbQuery.getStringField("item_name");
	return EXIT_SUCCESS;
}

int CSqlite3Helper::ReadItemByName(const string item_name, string & item_id)
{
	string sSqlCmd = "select * from game_items where item_name = '" + item_name + "' ";
	CppSQLite3Query dbQuery = db.execQuery(sSqlCmd.c_str());

	if (dbQuery.eof())
		return EXIT_FAILURE;

	item_id = dbQuery.getStringField("item_id");
	return EXIT_SUCCESS;
}

int CSqlite3Helper::WriteItem(const int token, const string item_id, const string item_name, const string item_name_zh)
{
	string sSqlCmd = "";
	int iRet = 0;

	switch (token)
	{
	case TRANS_BEGAN:
		db.execDML("begin transaction;");
		break;
	case TRANS_DATA:
		sSqlCmd = "insert into game_items (item_id,item_name,item_name_zh) values ('" + item_id + "','" + item_name + "','" + item_name_zh + "')";
		db.execDML(ASCIIToUTF8(sSqlCmd.c_str()));
		break;
	case TRANS_END:
		db.execDML("commit transaction;");
		break;
	default:
		TRACE("不支持的选项（%d）！\n", token);
		break;
	}

// 	sSqlCmd = "insert into game_items (item_id,item_name) values ('" + item_id + "','" + item_name + "')";
// 	iRet = db.execDML(sSqlCmd.c_str());
// 	if (iRet == 0)
// 		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int CSqlite3Helper::DeleteAllItems()
{
	string sSqlCmd = "delete from game_items";
	db.execQuery(sSqlCmd.c_str());

	sSqlCmd = "update sqlite_sequence SET seq = 0 where name ='game_items'";
	db.execQuery(sSqlCmd.c_str());

	return EXIT_SUCCESS;
}

CppSQLite3Query CSqlite3Helper::GetAllItems()
{
	char sSqlCmd[256];
	sprintf_s(sSqlCmd, "select * from game_items");

	CppSQLite3Query dbQuery = db.execQuery(sSqlCmd);

	return dbQuery;
}

// 城市表操作接口
int CSqlite3Helper::ReadStageByPos(const int pos, string & stage_id, string & stage_name)
{
	string sSqlCmd = "select * from game_stages where Id = '" + Int2STDStr(pos) + "' ";
	CppSQLite3Query dbQuery = db.execQuery(sSqlCmd.c_str());

	if (dbQuery.eof())
		return EXIT_FAILURE;

	stage_id = dbQuery.getStringField("stage_id");
	stage_name = dbQuery.getStringField("stage_name");

	return EXIT_SUCCESS;
}

int CSqlite3Helper::ReadStageById(const string stage_id, string & stage_name)
{
	string sSqlCmd = "select * from game_stages where stage_id = '" + stage_id + "' ";
	CppSQLite3Query dbQuery = db.execQuery(sSqlCmd.c_str());

	if (dbQuery.eof())
		return EXIT_FAILURE;

	stage_name = dbQuery.getStringField("stage_name");
	return EXIT_SUCCESS;
}

int CSqlite3Helper::ReadStageByName(const string stage_name, string & stage_id)
{
	string sSqlCmd = "select * from game_stages where stage_name = '" + stage_name + "' ";
	CppSQLite3Query dbQuery = db.execQuery(sSqlCmd.c_str());

	if (dbQuery.eof())
		return EXIT_FAILURE;

	stage_id = dbQuery.getStringField("stage_id");
	return EXIT_SUCCESS;
}

int CSqlite3Helper::WriteStage(const int token, const string stage_id, const string stage_name, const string stage_name_zh)
{
	string sSqlCmd = "";
	int iRet = 0;

	switch (token)
	{
	case TRANS_BEGAN:
		db.execDML("begin transaction;");
		break;
	case TRANS_DATA:
		sSqlCmd = "insert into game_stages (stage_id,stage_name,stage_name_zh) values ('" + stage_id + "','" + stage_name + "','" + stage_name_zh + "')";
		db.execDML(ASCIIToUTF8(sSqlCmd.c_str()));
		break;
	case TRANS_END:
		db.execDML("commit transaction;");
		break;
	default:
		TRACE("不支持的选项（%d）！\n", token);
		break;
	}

	return EXIT_SUCCESS;
}

int CSqlite3Helper::DeleteAllStages()
{
	string sSqlCmd = "delete from game_stages";
	db.execQuery(sSqlCmd.c_str());

	sSqlCmd = "update sqlite_sequence SET seq = 0 where name ='game_stages'";
	db.execQuery(sSqlCmd.c_str());

	return EXIT_SUCCESS;
}

CppSQLite3Query CSqlite3Helper::GetAllStages()
{
	char sSqlCmd[256];
	sprintf_s(sSqlCmd, "select * from game_stages");

	CppSQLite3Query dbQuery = db.execQuery(sSqlCmd);

	return dbQuery;
}
