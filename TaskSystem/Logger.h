#pragma once
#include "global.h"
#include "LogQueue.h"

class Logger 
{
public:
	static  Logger& GetInstance()
	{
		static  Logger single;
		return single;
	}
	// ������Ĭ�Ϲ��캯�����ڵ���
	Logger();
	Logger(const Logger&& other) = delete;
	Logger& operator = (const Logger&& other) = delete;
	Logger(const Logger& other) = delete;
	Logger& operator = (const Logger& other) = delete;
	Logger(const std::string& filename, bool console_output = false, size_t max_file_size_kb = 100, int num_threads = 3);
	~Logger();

	template<typename ...Args>
	void log(LogLevel Loglevel, const std::string& format, Args&& ...args);
	template<typename... Args>
	void console_log(LogLevel level, const std::string& format, Args&&... args);


private:
	void open_log_file();

	void check_and_rotate_log_file();

	size_t get_file_size();

	void rotate_log_file();

	//ʱ���
	std::string get_time();
	// ʹ��ģ���۵���ʽ����־��Ϣ��֧�� "{}" ռλ��
	template<typename... Args>
	std::string formatMessage(const std::string& format, Args&&... args);



	std::vector<std::thread> _work_threads;;
	std::ofstream _log_file;
	std::atomic<bool> _exit_flag;
	LogQueue _log_queue;
	bool _console_output; // �����Ƿ����������̨
	size_t _max_file_size;
	std::string _base_filename;
	int _current_log_index = 0;
	std::mutex mtx; // ��������������־���
	int _num_threads;
};

