#include "DatabaseManager.h"
#include "Logger.h"
DatabaseManager::DatabaseManager(const char* DB_NAME, const char* DB_KEY):_DB_NAME(DB_NAME), _DB_KEY(DB_KEY)
{
	create_database();
}

void DatabaseManager::create_database()
{
    sqlite3* db;
    int rc = sqlite3_open(_DB_NAME, &db);
    if (rc) {
        std::cerr << "无法打开数据库: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "创建数据库无法打开数据库。");
        return;
    }

    // 设置加密密钥（首次创建时加密）
    rc = sqlite3_key(db, _DB_KEY, strlen(_DB_KEY));
    if (rc != SQLITE_OK) {
        std::cerr << "设置密钥失败: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "创建数据库时设置密钥失败。");
        sqlite3_close(db);
        return;
    }

    const char* create_table_sql =
        "CREATE TABLE IF NOT EXISTS user_pwd_1 ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "pwd TEXT NOT NULL);";

    rc = sqlite3_exec(db, create_table_sql, nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "建表失败: " << sqlite3_errmsg(db) << std::endl;
        Logger::GetInstance().log(LogLevel::ERROR, "数据库和表创建失败。");
    }
    else {
		Logger::GetInstance().log(LogLevel::INFO, "数据库和表创建成功。");
    }

    sqlite3_close(db);
}

void DatabaseManager::insert_user_pwd(const std::string& user_name, const std::string& pwd)
{
    sqlite3* db;
    int rc = sqlite3_open(_DB_NAME, &db);
    if (rc) {
        std::cerr << "无法打开数据库: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "插入用户时无法打开数据库。");
        return;
    }

    // 访问加密数据库必须设置密码
    rc = sqlite3_key(db, _DB_KEY, strlen(_DB_KEY));
    if (rc != SQLITE_OK) {
        std::cerr << "设置密钥失败: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "插入用户时设置密钥失败。");
        sqlite3_close(db);
        return;
    }

    const char* sql = "INSERT INTO user_pwd_1 (name, pwd) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL准备失败: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "插入用户时SQL准备失败。");
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, user_name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, pwd.c_str(), -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        std::cout << "用户插入成功！" << std::endl;
		Logger::GetInstance().log(LogLevel::INFO, "用户 {} 插入成功。", user_name);
    }
    else {
        std::cerr << "插入失败: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "用户 {} 插入失败。", user_name);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void DatabaseManager::verify_user(const std::string& user_name, const std::string& pwd, bool& verify_status)
{
    sqlite3* db;
    int rc = sqlite3_open(_DB_NAME, &db);
    if (rc) {
        std::cerr << "无法打开数据库: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "查询用户时无法打开数据库。");
        return;
    }

    // 设置密码访问加密数据库
    rc = sqlite3_key(db, _DB_KEY, strlen(_DB_KEY));
    if (rc != SQLITE_OK) {
        std::cerr << "设置密钥失败: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "查询用户时设置密钥失败。");
        sqlite3_close(db);
        return;
    }

    const char* sql = "SELECT * FROM user_pwd_1 WHERE name = ? AND pwd = ?;";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL准备失败: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "查询用户时SQL准备失败。");
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, user_name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, pwd.c_str(), -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        std::cout << "用户验证成功！" << std::endl;
        verify_status = true; // 设置验证状态为成功
		Logger::GetInstance().log(LogLevel::INFO, "{} 验证成功。", user_name);
    }
    else {
        std::cout << "用户名或密码错误！" << std::endl;
        verify_status = false; // 设置验证状态为失败
		Logger::GetInstance().log(LogLevel::INFO, "用户名或密码错误。");

    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
