#pragma once
#include <string>
#include <memory>
#include <sqlite3.h>
#include <sqlite3mc.h>
#include "global.h"
class DatabaseManager
{
public:
	DatabaseManager(const char* DB_NAME, const char* DB_KEY);
	void create_database();
	void insert_user_pwd(const std::string& user_name, const std::string& pwd);
	void verify_user(const std::string& user_name, const std::string& pwd, bool& verify_status);

private:
	const char*  _DB_NAME;
	const char* _DB_KEY; // Êı¾İ¿â¼ÓÃÜÃÜÂë
};

