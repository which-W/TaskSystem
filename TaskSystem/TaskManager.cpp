#include"TaskManager.h"
#include "../includes/nlohmann/json.hpp"
// ʹ�� nlohmann �����ռ�򻯴���
using json = nlohmann::json;
TaskManager::TaskManager() :next_Id(1)
{
	loadTasks();

}

void TaskManager::loadTasks()
{
	std::ifstream inFile("tasks.json");
	if (!inFile.is_open()) {
		Logger::GetInstance().log(LogLevel::INFO, "�����ļ������ڣ���ʼ�½���");
		inFile.peek();  // �鿴��һ���ַ������ƶ�ָ��
		if (inFile.eof()) {
			std::cout << "�ļ�Ϊ��" << std::endl;
			return;
		}
		return;
	}

	// ��ȡ�����ļ�����
	std::string jsonData((std::istreambuf_iterator<char>(inFile)),
		std::istreambuf_iterator<char>());

	// �ر��ļ�
	inFile.close();

	// ���� JSON ����
	json jsonDataParsed = json::parse(jsonData);
	// ���� JSON �����е�ÿ���������
	for (const auto& item : jsonDataParsed) {
		Task task;
		task.id = item.at("id").get<int>();       // ��� key �����ڻ����Ͳ��ԣ������쳣
		task.description = item.at("description").get<std::string>();
		task.priority = item.at("priority").get<int>();
		task.dueDate = item.at("dueDate").get<std::string>();

		tasks.push_back(task);
		Logger::GetInstance().log(LogLevel::INFO, "��������ɹ���");
		if (task.id >= next_Id) {
			next_Id = task.id + 1;
		}
	}

}

void TaskManager::addTask(const std::string& description, int priority, const std::string& dueDate)
{
	Task task;
	task.id = next_Id++;
	task.description = description;
	task.priority = priority;
	task.dueDate = dueDate;
	tasks.push_back(task);
	Logger::GetInstance().log(LogLevel::INFO, "�������ɹ���", "task add ", task.toString());
	saveTasks();//���������ļ�
}

void TaskManager::saveTasks() const
{
	std::ofstream outFile("tasks.json");
	if (!outFile) {
		Logger::GetInstance().log(LogLevel::ERROR, "�޷��������ļ����б��档");
		return;
	}

	try {
		json jsonData = json::array();

		for (const auto& task : tasks) {
			json taskJson;
			taskJson["id"] = task.id;
			taskJson["description"] = task.description;
			taskJson["priority"] = task.priority;
			taskJson["dueDate"] = task.dueDate;

			jsonData.push_back(taskJson);
		}

		outFile << jsonData.dump(4); // ������ʽ
	}
	catch (const std::exception& e) {
		Logger::GetInstance().log(LogLevel::ERROR, "��������ʱ�����쳣: ", e.what());
	}

	outFile.close();
	Logger::GetInstance().log(LogLevel::INFO, "��������ɹ���");
}

void TaskManager::listTasks(int sortOption) const
{
	std::vector<Task> sortedTasks = tasks;

	// ��������ѡ���������
	switch (sortOption) {
	case 1:
		std::sort(sortedTasks.begin(), sortedTasks.end(), compareByPriority);
		break;
	case 2:
		std::sort(sortedTasks.begin(), sortedTasks.end(), compareByDueDate);
		break;
	default:
		break; // Ĭ�ϰ� ID ����
	}

	// ��ӡ�����б�
	for (const auto& task : sortedTasks) {
		std::cout << task.toString() << std::endl;
	}
}

void TaskManager::updateTask(int id, const std::string& description, int priority, const std::string& dueDate) {
	for (auto& task : tasks) {
		if (task.id == id) {
			Logger::GetInstance().log(LogLevel::INFO, "����ǰ����: " + task.toString());
			task.description = description;
			task.priority = priority;
			task.dueDate = dueDate;
			Logger::GetInstance().log(LogLevel::INFO, "���º�����: " + task.toString());
			saveTasks();
			return;
		}
	}
	std::cout << "δ�ҵ�IDΪ " << id << " ������" << std::endl;
}

void TaskManager::deleteTask(int id) {
	auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& task) {
		return task.id == id;
		});
	std::cout << it->toString() << std::endl;
	if (it != tasks.end()) {
		std::string taskInfo = it->toString();
		tasks.erase(it);
		Logger::GetInstance().log(LogLevel::INFO, "ɾ������: " + taskInfo);
		saveTasks();
	}
	else {
		std::cout << "δ�ҵ�IDΪ " << id << " ������" << std::endl;
	}
}

void TaskManager::upgrate_index() {
	next_Id = 1;
	for (auto& task : tasks)
	{
		task.id = next_Id++;
		saveTasks();
	}
	return;
}

bool TaskManager::compareByPriority(const Task& a, const Task& b) {
	return a.priority < b.priority;
}

bool TaskManager::compareByDueDate(const Task& a, const Task& b) {
	return a.dueDate < b.dueDate;
}


