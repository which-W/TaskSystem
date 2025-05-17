#pragma once
#include "global.h"
#include "TaskManager.h"
//�麯������ʱ��Ҫ�����ģ��
class CommandBase {
public:
    virtual void execute(const std::string& args) = 0;
};

// CRTP ����ģ��
template<typename Derived>
class Command : public CommandBase
{
public:
    void execute(const std::string& args)
    {
        (static_cast<Derived*>(this))->executeImpl(args);
    }
private:

};
// �����������
class AddCommand :public Command<AddCommand>
{
public:
    AddCommand(TaskManager& manager) :taskManager(manager) {};
    void executeImpl(const std::string& args);

private:
    TaskManager& taskManager;
};

// ɾ����������
class DeleteCommand : public Command<DeleteCommand> {
public:
    DeleteCommand(TaskManager& manager) : taskManager(manager) {}
    void executeImpl(const std::string& args);
private:
    TaskManager& taskManager;
};

// �г���������
class ListCommand : public Command<ListCommand> {
public:
    ListCommand(TaskManager& manager) : taskManager(manager) {}
    void executeImpl(const std::string& args);
private:
    TaskManager& taskManager;
};

// ������������
class UpdateCommand : public Command<UpdateCommand> {
public:
    UpdateCommand(TaskManager& manager) : taskManager(manager) {};
    void executeImpl(const std::string& args);
private:
    TaskManager& taskManager;
};

// ������������
class Update_IndexCommand : public Command<Update_IndexCommand> {
public:
    Update_IndexCommand(TaskManager& manager) : taskManager(manager) {};
    void executeImpl(const std::string& args);
private:
    TaskManager& taskManager;
};