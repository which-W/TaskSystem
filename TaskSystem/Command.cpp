#include "Command.h"
#include "TaskManager.h"
void AddCommand::executeImpl(const std::string& args) {
    // �򵥵Ĳ�������������,���ȼ�,��ֹ����
    //�ҵ��������ŵ�λ��
    size_t pos1 = args.find(',');
    size_t pos2 = args.find(',', pos1 + 1);
	size_t pos3 = args.find(',', pos2 + 1);
    if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos) {
        std::cout << "������ʽ������ʹ��: add <����>,<������>,<���ȼ�>,<��ֹ����>" << std::endl;
        return;
    }
    // ��ȡ���������ȼ��ͽ���ʱ��
    std::string description = args.substr(0, pos1);
	std::string owner = args.substr(pos1 + 1, pos2 - pos1 - 1);
    int priority = std::stoi(args.substr(pos2 + 1, pos3 - pos2 - 1));
    std::string dueDate = args.substr(pos3 + 1);
    std::cout << description << std::endl;
	std::cout << owner << std::endl;
    std::cout << priority << std::endl;
    std::cout << dueDate << std::endl;
    taskManager.addTask(description,owner, priority, dueDate);
    std::cout << "������ӳɹ���" << std::endl;
}

void DeleteCommand::executeImpl(const std::string& args) {
    try {
        size_t pos;
        int id = std::stoi(args, &pos);
        if (pos != args.length()) {
            std::cout << "������ʽ������ʹ��: delete <ID>" << std::endl;
            return;
        }
        taskManager.deleteTask(id);
        std::cout << "����ɾ���ɹ���" << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "������ʽ������ʹ��: delete <ID>" << std::endl;
        return;
    }
    catch (const std::out_of_range& e) {
        std::cout << "ID������Χ����ʹ����Ч������ID��" << std::endl;
        return;
    }
    catch (const std::exception& e) {
        std::cout << "ɾ������ʱ�����쳣: " << e.what() << std::endl;
        return;
    }
    catch (...) {
        std::cout << "����δ֪����" << std::endl;
        return;
    }
}

void ListCommand::executeImpl(const std::string& args) {
    int sortOption = 0;
    if (!args.empty()) {
        sortOption = std::stoi(args);
    }
    taskManager.listTasks(sortOption);
}

void UpdateCommand::executeImpl(const std::string& args) {
    // ������ʽ: ID,����,���ȼ�,��ֹ����
    size_t pos1 = args.find(',');
    size_t pos2 = args.find(',', pos1 + 1);
    size_t pos3 = args.find(',', pos2 + 1);
	size_t pos4 = args.find(',', pos3 + 1);
    if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos || pos4 == std::string::npos) {
        std::cout << "������ʽ������ʹ��: update <ID>,<����>,<���ȼ�>,<��ֹ����>" << std::endl;
        return;
    }
    int id = std::stoi(args.substr(0, pos1));
    std::string description = args.substr(pos1 + 1, pos2 - pos1 - 1);
	std::string owner = args.substr(pos2 + 1, pos3 - pos2 - 1);
    int priority = std::stoi(args.substr(pos3 + 1, pos4 - pos3 - 1));
    std::string dueDate = args.substr(pos4 + 1);
    taskManager.updateTask(id, description, owner,priority, dueDate);
    std::cout << "������³ɹ���" << std::endl;
}

void Update_IndexCommand::executeImpl(const std::string& args) {
    taskManager.upgrate_index();
    std::cout << "�������³ɹ���" << std::endl;
}

void SelectByOwnerCommand::executeImpl(const std::string& args)
{
	if (args.empty()) {
		std::cout << "���ṩ���������ơ�" << std::endl;
		return;
	}
	taskManager.selectByOwner(args);
}

void HelpCommand::executeImpl(const std::string& args)
{
	size_t pos1 = args.find(' ');
    std::string command = args.substr(0, pos1);
    if (command == "add") {
        std::cout << "add <����>,<������>,<���ȼ�>,<��ֹ����> - �������" << std::endl;
	}
	else if (command == "delete") {
		std::cout << "delete <ID> - ɾ��ָ��ID������" << std::endl;
	}
	else if (command == "list") {
		std::cout << "list [sortOption] - �г���������sortOption��ѡ��0-��ID, 1-�����ȼ�, 2-����ֹ����" << std::endl;
	}
	else if (command == "update") {
		std::cout << "update <ID>,<����>,<������>,<���ȼ�>,<��ֹ����> - ����ָ��ID������" << std::endl;
	}
	else if (command == "upgrate_index") {
		std::cout << "upgrate_index - ��������" << std::endl;
	}
	else if (command == "slowner") {
		std::cout << "slowner <������> - ����������ɸѡ����" << std::endl;
	}
    else if (command == " ") {
        std::cout << "add <����>,<������>,<���ȼ�>,<��ֹ����> - �������" << std::endl;
		std::cout << "delete <ID> - ɾ��ָ��ID������" << std::endl;
		std::cout << "list [sortOption] - �г���������sortOption��ѡ��0-��ID, 1-�����ȼ�, 2-����ֹ����" << std::endl;
		std::cout << "update <ID>,<����>,<������>,<���ȼ�>,<��ֹ����> - ����ָ��ID������" << std::endl;
		std::cout << "upgrate_index - ��������" << std::endl;
		std::cout << "slowner <������> - ����������ɸѡ����" << std::endl;
    }
	else {
		std::cout << "δ֪���" << command << std::endl;
		std::cout << "��������: add, delete, list, update, upgrate_index, slowner" << std::endl;
	}
}
