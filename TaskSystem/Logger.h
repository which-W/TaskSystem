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
	void log(LogLevel Loglevel, const std::string& format, Args&& ...args) {
		std::lock_guard<std::mutex> lock(mtx);
		std::string loglevel_str;
		switch (Loglevel) {
		case LogLevel::INFO: loglevel_str = "[INFO] "; break;
		case LogLevel::DEBUG: loglevel_str = "[DEBUG] "; break;
		case LogLevel::ERROR: loglevel_str = "[ERROR] "; break;
		}
		_log_queue.push(loglevel_str + formatMessage(format, std::forward<Args>(args)...));
	}

	template<typename... Args>
	void console_log(LogLevel level, const std::string& format, Args&&... args) {
		std::lock_guard<std::mutex> lock(mtx);
		std::string loglevel_str;
		switch (level) {
		case INFO: loglevel_str = "[INFO] "; break;
		case DEBUG: loglevel_str = "[DEBUG] "; break;
		case WARN: loglevel_str = "[WARN] "; break;
		case ERROR: loglevel_str = "[ERROR] "; break;
		}
		std::cout << (loglevel_str + formatMessage(format, std::forward<Args>(args)...)) << std::endl;
	}

	


private:
	void open_log_file();

	void check_and_rotate_log_file();

	size_t get_file_size();

	void rotate_log_file();

	//ʱ���
	std::string get_time();
	// ʹ��ģ���۵���ʽ����־��Ϣ��֧�� "{}" ռλ��
	template<typename... Args>
	std::string formatMessage(const std::string& format, Args&&... args) {
		std::vector<std::string> arg_strings = { to_string_helper(std::forward<Args>(args))... };
		std::ostringstream oss;
		size_t arg_index = 0;
		size_t pos = 0;
		size_t placeholder = format.find("{}", pos);

		while (placeholder != std::string::npos) {
			oss << format.substr(pos, placeholder - pos);
			if (arg_index < arg_strings.size()) {
				oss << arg_strings[arg_index++];
			}
			else {
				// û���㹻�Ĳ��������� "{}"
				oss << "{}";
			}
			pos = placeholder + 2; // ���� "{}"
			placeholder = format.find("{}", pos);
		}

		// ���ʣ����ַ���
		oss << format.substr(pos);

		// �������ʣ��Ĳ�������ԭ��ʽƴ��
		while (arg_index < arg_strings.size()) {
			oss << arg_strings[arg_index++];
		}

		return "[" + get_time() + "] " + oss.str();
	}



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

