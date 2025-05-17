#include "Command.h"
#include "TaskManager.h"
void AddCommand::executeImpl(const std::string& args) {
    // �򵥵Ĳ�������������,���ȼ�,��ֹ����
    //�ҵ��������ŵ�λ��
    size_t pos1 = args.find(',');
    size_t pos2 = args.find(',', pos1 + 1);
    if (pos1 == std::string::npos || pos2 == std::string::npos) {
        std::cout << "������ʽ������ʹ��: add <����>,<���ȼ�>,<��ֹ����>" << std::endl;
        return;
    }
    // ��ȡ���������ȼ��ͽ���ʱ��
    std::string description = args.substr(0, pos1);
    int priority = std::stoi(args.substr(pos1 + 1, pos2 - pos1 - 1));
    std::string dueDate = args.substr(pos2 + 1);
    std::cout << description << std::endl;
    std::cout << priority << std::endl;
    std::cout << dueDate << std::endl;
    taskManager.addTask(description, priority, dueDate);
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
    if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos) {
        std::cout << "������ʽ������ʹ��: update <ID>,<����>,<���ȼ�>,<��ֹ����>" << std::endl;
        return;
    }
    int id = std::stoi(args.substr(0, pos1));
    std::string description = args.substr(pos1 + 1, pos2 - pos1 - 1);
    int priority = std::stoi(args.substr(pos2 + 1, pos3 - pos2 - 1));
    std::string dueDate = args.substr(pos3 + 1);
    taskManager.updateTask(id, description, priority, dueDate);
    std::cout << "������³ɹ���" << std::endl;
}

void Update_IndexCommand::executeImpl(const std::string& args) {
    taskManager.upgrate_index();
    std::cout << "�������³ɹ���" << std::endl;
}