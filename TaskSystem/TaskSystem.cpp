// TaskSystem.cpp: 定义应用程序的入口点。
//
#include "global.h"
#include "TaskManager.h"
#include "Command.h"
#include "Logger.h"
#include "CommandWrapper.h"
#include "Register_Command.h"
#include "Run_command.h"
int main()
{	
	TaskManager taskManager;
	initCommandMap(taskManager);
	// 加载任务数据
	std::unordered_map<std::string, CommandWrapper>& commandMap = getCommandMap();
	runloop(commandMap);
	return 0;
}
