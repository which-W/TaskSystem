#include "Run_command.h"
#include <iostream>

void runCommandLoop(std::unordered_map<std::string, CommandWrapper>& commandMap) {
    std::cout << "��ӭʹ���������ϵͳ��" << std::endl;
    std::cout << "��������: add, delete, list, update, exit, upgrate_index set_owner list_owner get_owner �������ݴ���" << std::endl;
    std::cout << "���� 'help add ���� help' �鿴�������ʹ�÷�����" << std::endl;
    std::string input;

    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, input);

        if (input.empty()) {
            continue;
        }

        if (input == "exit") {
            std::cout << "�˳��������ϵͳ��" << std::endl;
            break;
        }

        // �ָ�����Ͳ���
        size_t spacePos = input.find(' ');
        std::string cmd = input.substr(0, spacePos);
        std::string args = (spacePos != std::string::npos) ? input.substr(spacePos + 1) : "";

        auto it = commandMap.find(cmd);
        if (it != commandMap.end()) {
            it->second.execute(args);  // ʹ��ָ�����
        }
        else {
            std::cout << "δ֪���" << cmd << std::endl;
        }
    }
}