#include "Run_command.h"
#include <iostream>
#include "DatabaseManager.h"

DatabaseManager dbManager("user_pwd.db", "12345678wW");

void runloop(std::unordered_map<std::string, CommandWrapper>& commandMap) {
    
    runVerificationLoop(commandMap); // ������֤ѭ��
}

void runVerificationLoop(std::unordered_map<std::string, CommandWrapper>& commandMap)
{
    std::cout << "��ӭ�����������ϵͳ��loginҳ��,������˳�Ȼ��������q��exit�˳�����" << std::endl;
    // �û���¼��֤
    while (true) {
        //ע���û�
        std::string register_choice;
        std::cout << "�Ƿ�ע�����û����������y,��������˺���n(y/n): ";
        std::getline(std::cin, register_choice);
        if (register_choice == "y" || register_choice == "Y") {
            std::string user_name, pwd;
            std::cout << "�������û���: ";
            std::getline(std::cin, user_name);
            std::cout << "����������: ";
            std::getline(std::cin, pwd);
            dbManager.insert_user_pwd(user_name, pwd);
            std::cout << "�û�ע��ɹ���" << std::endl;
		}
		else if (register_choice == "q" || register_choice == "exit") {
			std::cout << "�˳��������ϵͳ��" << std::endl;
			return; // �˳���֤ѭ��
		}
		else if (register_choice == "n" || register_choice == "N") {
			std::cout << "���¼�����˺š�" << std::endl;
		}
        else if (register_choice != "n" && register_choice != "N") {
            std::cout << "��Ч���룬������ y �� n��" << std::endl;
            continue; // ����ѯ��
        }
        std::string user_name, pwd;
        std::cout << "�������û���: ";
        std::getline(std::cin, user_name);
        std::cout << "����������: ";
        std::getline(std::cin, pwd);
		bool verify_status = false;
        // ��֤�û�
        dbManager.verify_user(user_name, pwd, verify_status);
		if (verify_status == false) {
			std::cout << "�û���������������������롣" << std::endl;
			continue; // ���������û���������
		}
        if (!user_name.empty() && !pwd.empty() && verify_status) {
            break; // �ɹ���¼���˳�ѭ��
        }
    };
	runCommandLoop(commandMap); // ��������ѭ��
}

void runCommandLoop(std::unordered_map<std::string, CommandWrapper>& commandMap) {
    std::cout << "��ӭʹ���������ϵͳ��" << std::endl;
    std::cout << "��������: add, delete, list, update, exit, upgrate_index set_owner list_owner get_owner �������ݴ���" << std::endl;
    std::cout << "���� help add �鿴�������ʹ�÷�����" << std::endl;
    std::string input;

    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, input);

        if (input.empty()) {
            continue;
        }

        if (input == "exit") {
            std::cout << "�����û���¼����" << std::endl;
			runVerificationLoop(commandMap); // ���½�����֤ѭ��
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
};