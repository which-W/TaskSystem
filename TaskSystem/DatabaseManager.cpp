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
        std::cerr << "�޷������ݿ�: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "�������ݿ��޷������ݿ⡣");
        return;
    }

    // ���ü�����Կ���״δ���ʱ���ܣ�
    rc = sqlite3_key(db, _DB_KEY, strlen(_DB_KEY));
    if (rc != SQLITE_OK) {
        std::cerr << "������Կʧ��: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "�������ݿ�ʱ������Կʧ�ܡ�");
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
        std::cerr << "����ʧ��: " << sqlite3_errmsg(db) << std::endl;
        Logger::GetInstance().log(LogLevel::ERROR, "���ݿ�ͱ���ʧ�ܡ�");
    }
    else {
		Logger::GetInstance().log(LogLevel::INFO, "���ݿ�ͱ����ɹ���");
    }

    sqlite3_close(db);
}

void DatabaseManager::insert_user_pwd(const std::string& user_name, const std::string& pwd)
{
    sqlite3* db;
    int rc = sqlite3_open(_DB_NAME, &db);
    if (rc) {
        std::cerr << "�޷������ݿ�: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "�����û�ʱ�޷������ݿ⡣");
        return;
    }

    // ���ʼ������ݿ������������
    rc = sqlite3_key(db, _DB_KEY, strlen(_DB_KEY));
    if (rc != SQLITE_OK) {
        std::cerr << "������Կʧ��: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "�����û�ʱ������Կʧ�ܡ�");
        sqlite3_close(db);
        return;
    }

    const char* sql = "INSERT INTO user_pwd_1 (name, pwd) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL׼��ʧ��: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "�����û�ʱSQL׼��ʧ�ܡ�");
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, user_name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, pwd.c_str(), -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        std::cout << "�û�����ɹ���" << std::endl;
		Logger::GetInstance().log(LogLevel::INFO, "�û� {} ����ɹ���", user_name);
    }
    else {
        std::cerr << "����ʧ��: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "�û� {} ����ʧ�ܡ�", user_name);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void DatabaseManager::verify_user(const std::string& user_name, const std::string& pwd, bool& verify_status)
{
    sqlite3* db;
    int rc = sqlite3_open(_DB_NAME, &db);
    if (rc) {
        std::cerr << "�޷������ݿ�: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "��ѯ�û�ʱ�޷������ݿ⡣");
        return;
    }

    // ����������ʼ������ݿ�
    rc = sqlite3_key(db, _DB_KEY, strlen(_DB_KEY));
    if (rc != SQLITE_OK) {
        std::cerr << "������Կʧ��: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "��ѯ�û�ʱ������Կʧ�ܡ�");
        sqlite3_close(db);
        return;
    }

    const char* sql = "SELECT * FROM user_pwd_1 WHERE name = ? AND pwd = ?;";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL׼��ʧ��: " << sqlite3_errmsg(db) << std::endl;
		Logger::GetInstance().log(LogLevel::ERROR, "��ѯ�û�ʱSQL׼��ʧ�ܡ�");
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, user_name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, pwd.c_str(), -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        std::cout << "�û���֤�ɹ���" << std::endl;
        verify_status = true; // ������֤״̬Ϊ�ɹ�
		Logger::GetInstance().log(LogLevel::INFO, "{} ��֤�ɹ���", user_name);
    }
    else {
        std::cout << "�û������������" << std::endl;
        verify_status = false; // ������֤״̬Ϊʧ��
		Logger::GetInstance().log(LogLevel::INFO, "�û������������");

    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
