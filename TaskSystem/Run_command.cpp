#include "Run_command.h"
#include <iostream>

void runCommandLoop(std::unordered_map<std::string, CommandWrapper>& commandMap) {
    std::cout << "欢迎使用任务管理系统！" << std::endl;
    std::cout << "可用命令: add, delete, list, update, exit, upgrate_index set_owner list_owner get_owner 进行数据处理" << std::endl;
    std::cout << "输入 'help add 或者 help' 查看命令具体使用方法。" << std::endl;
    std::string input;

    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, input);

        if (input.empty()) {
            continue;
        }

        if (input == "exit") {
            std::cout << "退出任务管理系统。" << std::endl;
            break;
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
}