#pragma once
#include "global.h"
#include "TaskManager.h"
#include "Command.h"
#include "CommandWrapper.h"
 
std::unordered_map<std::string, CommandWrapper> commandMap;
//CRTP¹¹½¨
void initCommandMap(TaskManager& taskManager) {
	commandMap.emplace("add", AddCommand(taskManager));
	commandMap.emplace("delete", DeleteCommand(taskManager));
	commandMap.emplace("list", ListCommand(taskManager));
	commandMap.emplace("update", UpdateCommand(taskManager));
	commandMap.emplace("upgrate_index", Update_IndexCommand(taskManager));
	commandMap.emplace("list_owner", SelectByOwnerCommand(taskManager));
	commandMap.emplace("help", HelpCommand(taskManager));
	commandMap.emplace("get_owner", GetTaskOwnerCommand(taskManager));
	commandMap.emplace("set_owner", ModifyTaskOwnerCommand(taskManager));
};

std::unordered_map<std::string, CommandWrapper> &getCommandMap() {
	return commandMap;
}