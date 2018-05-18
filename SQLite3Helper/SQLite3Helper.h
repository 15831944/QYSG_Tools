#pragma once
#include "CppSQLite3.h"
#include <iostream>
using namespace std;

#define DB_DEFAULT_NAME ".\\profile\\qysg.sqlite3"

enum TransactionToken {
	TRANS_BEGAN = 1,
	TRANS_DATA,
	TRANS_END,
};

class CSqlite3Helper
{
public:
	CSqlite3Helper();
	virtual ~CSqlite3Helper();

private:
	CppSQLite3DB db;

public:
	int Open(); // use dafault name: qysg.sqlite3
	int Open(char *dbName);
	void Close();

	bool ExistProfile(string app_name, string key);
	int ReadProfileValue(string app_name, string key, string & value);
	int WriteProfileValue(string app_name, string key, string value);
	void TestProfileInterface();

	bool ExistProfileFile(string file_name);
	int ReadProfileFile(string file_name, string & timestamp);
	int WriteProfileFile(string file_name, string timestamp);
	void TestProfileFileInterface();

	int ReadItemByPos(const int pos, string & item_id, string & item_name);
	int ReadItemById(const string item_id, string & item_name);
	int ReadItemByName(const string item_name, string & item_id);
	int WriteItem(const int token, const string item_id, const string item_name, const string item_name_zh);
	int DeleteAllItems();
	CppSQLite3Query GetAllItems();

	int ReadStageByPos(const int pos, string & stage_id, string & stage_name);
	int ReadStageById(const string stage_id, string & stage_name);
	int ReadStageByName(const string stage_name, string & stage_id);
	int WriteStage(const int token, const string stage_id, const string stage_name, const string stage_name_zh);
	int DeleteAllStages();
	CppSQLite3Query GetAllStages();

private:
	int InitializeTables();
};