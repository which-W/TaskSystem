#include "Logger.h"
namespace fs = std::filesystem;

Logger::Logger() : _exit_flag(false),
_console_output(false),
_max_file_size(100 * 1024),
_base_filename("Task.log"),
_num_threads(3) {
	open_log_file();
	if (!_log_file) {
		throw std::runtime_error("log file open is error");
	}
	for (int i = 1; i < _num_threads; i++) {
		_work_threads.emplace_back(std::thread([this]() {
			std::string msg;
			while (_log_queue.pop(msg)) {
				check_and_rotate_log_file();
				_log_file << msg << std::endl;
				if (_console_output) {
					std::cout << msg << std::endl;
				}
			}
			}));
	};
}

Logger::Logger(const std::string& filename, bool console_output = false, size_t max_file_size_kb = 100, int num_threads = 3) :_exit_flag(false)
, _console_output(console_output), _max_file_size(max_file_size_kb * 1024), _base_filename(filename), _num_threads(num_threads) {
	open_log_file();
	if (!_log_file) {
		throw std::runtime_error("log file open is error");
	}

	for (int i = 1; i < _num_threads; i++) {
		_work_threads.emplace_back(std::thread([this]() {
			std::string msg;
			while (_log_queue.pop(msg)) {
				check_and_rotate_log_file();
				_log_file << msg << std::endl;
				if (_console_output) {
					std::cout << msg << std::endl;
				}
			}
			}));
	};
}

Logger::~Logger() {
	_exit_flag = true;
	_log_queue.shutdown();
	for (auto& thread : _work_threads) {
		if (thread.joinable()) {
			thread.join();
		}
	}
	if (_log_file.is_open()) {
		_log_file.close();
	}
}

void Logger::open_log_file() {
	if (_log_file.is_open()) {
		_log_file.close();
	}
	_log_file.open(_base_filename, std::ios::out | std::ios::app);
}

void Logger::check_and_rotate_log_file() {
	if (get_file_size() >= _max_file_size) {
		rotate_log_file();
	}
}

size_t Logger::get_file_size() {
	if (!fs::exists(_base_filename)) {
		return 0;
	}
	return (size_t)fs::file_size(_base_filename);
}

void Logger::rotate_log_file() {
	_log_file.close();

	std::string new_log_name = _base_filename + "." + std::to_string(++_current_log_index);

	if (fs::exists(_base_filename)) {
		fs::rename(_base_filename, new_log_name);
	}


	open_log_file(); // ���µ���־�ļ�
}

//ʱ���
std::string Logger::get_time() {
	auto now = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(now);
	char buffer[100];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
	return std::string(buffer);
}

template<typename ...Args>
void Logger::log(LogLevel Loglevel, const std::string& format, Args&& ...args) {
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
void Logger::console_log(LogLevel level, const std::string& format, Args&&... args) {
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

template<typename... Args>
std::string Logger::formatMessage(const std::string& format, Args&&... args) {
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
