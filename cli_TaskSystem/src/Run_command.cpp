#include "Run_command.h"
#include <iostream>
#include "DatabaseManager.h"

DatabaseManager dbManager("user_pwd.db", "12345678wW");

void runloop(std::unordered_map<std::string, CommandWrapper>& commandMap) {
    
    runVerificationLoop(commandMap); // 进入验证循环
}

void runVerificationLoop(std::unordered_map<std::string, CommandWrapper>& commandMap)
{
    std::cout << "欢迎来到任务管理系统的login页面,如果想退出然可以输入q或exit退出程序。" << std::endl;
    // 用户登录验证
    while (true) {
        //注册用户
        std::string register_choice;
        std::cout << "是否注册新用户？如果是则y,如果已有账号则按n(y/n): ";
        std::getline(std::cin, register_choice);
        if (register_choice == "y" || register_choice == "Y") {
            std::string user_name, pwd;
            std::cout << "请输入用户名: ";
            std::getline(std::cin, user_name);
            std::cout << "请输入密码: ";
            std::getline(std::cin, pwd);
            dbManager.insert_user_pwd(user_name, pwd);
            std::cout << "用户注册成功！" << std::endl;
		}
		else if (register_choice == "q" || register_choice == "exit") {
			std::cout << "退出任务管理系统。" << std::endl;
			return; // 退出验证循环
		}
		else if (register_choice == "n" || register_choice == "N") {
			std::cout << "请登录已有账号。" << std::endl;
		}
        else if (register_choice != "n" && register_choice != "N") {
            std::cout << "无效输入，请输入 y 或 n。" << std::endl;
            continue; // 重新询问
        }
        std::string user_name, pwd;
        std::cout << "请输入用户名: ";
        std::getline(std::cin, user_name);
        std::cout << "请输入密码: ";
        std::getline(std::cin, pwd);
		bool verify_status = false;
        // 验证用户
        dbManager.verify_user(user_name, pwd, verify_status);
		if (verify_status == false) {
			std::cout << "用户名或密码错误，请重新输入。" << std::endl;
			continue; // 重新输入用户名和密码
		}
        if (!user_name.empty() && !pwd.empty() && verify_status) {
            break; // 成功登录，退出循环
        }
    };
	runCommandLoop(commandMap); // 进入命令循环
}

void runCommandLoop(std::unordered_map<std::string, CommandWrapper>& commandMap) {
    std::cout << "欢迎使用任务管理系统！" << std::endl;
    std::cout << "可用命令: add, delete, list, update, exit, upgrate_index set_owner list_owner get_owner 进行数据处理" << std::endl;
    std::cout << "输入 help add 查看命令具体使用方法。" << std::endl;
    std::string input;

    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, input);

        if (input.empty()) {
            continue;
        }

        if (input == "exit") {
            std::cout << "返回用户登录界面" << std::endl;
			runVerificationLoop(commandMap); // 重新进入验证循环
        }

        // 分割命令和参数
        size_t spacePos = input.find(' ');
        std::string cmd = input.substr(0, spacePos);
        std::string args = (spacePos != std::string::npos) ? input.substr(spacePos + 1) : "";

        auto it = commandMap.find(cmd);
        if (it != commandMap.end()) {
            it->second.execute(args);  // 使用指针调用
        }
        else {
            std::cout << "未知命令：" << cmd << std::endl;
        }
    }
};