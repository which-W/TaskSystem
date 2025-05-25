#pragma once
#include "../static/Task.h"
#include "../static/global.h"
#include "../plugins/Logger.h"

class TaskManager
{
public:
    TaskManager();
    void addTask(const std::string& description, std::string& owner,int priority, const std::string& dueDate);
    void deleteTask(int id);
    void updateTask(int id, const std::string& description, std::string& owner,  int priority, const std::string& dueDate);
    void listTasks(int sortOption = 0) const; // 0-按ID, 1-按优先级, 2-按截止日期
    void loadTasks();
    void saveTasks() const;
    void upgrate_index();
	void selectByOwner(const std::string& owner) const; // 根据所有者筛选任务
    void getTaskOwner(int id);
	void modifyTaskOwner(int id, const std::string& newOwner);
    ~TaskManager();

private:
    std::vector<Task> tasks;
    int next_Id;

    // 辅助排序函数
    static bool compareByPriority(const Task& a, const Task& b);
    static bool compareByDueDate(const Task& a, const Task& b);
};



