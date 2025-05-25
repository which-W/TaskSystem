// TaskSystem.cpp: 定义应用程序的入口点。
//
#include "./static/global.h"
#include "./src/Command.h"
#include "./plugins/Logger.h"
#include "./static/CommandWrapper.h"
#include "./src/Register_Command.h"
#include "./src/Run_command.h"
int main()
{	
	TaskManager taskManager;
	initCommandMap(taskManager);
	// 加载任务数据
	std::unordered_map<std::string, CommandWrapper>& commandMap = getCommandMap();
	runloop(commandMap);
	return 0;
}
