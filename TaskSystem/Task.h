#pragma once
#include"global.h"

struct Task
{
    int id;
    std::string description;
    int priority; // 1-��, 2-��, 3-��
    std::string dueDate; // ��ʽ: YYYY-MM-DD

    std::string toString() const {
        std::ostringstream oss;
        oss << "ID: " << id
            << ", ����: " << description
            << ", ���ȼ�: " << priority
            << ", ��ֹ����: " << dueDate;
        return oss.str();
    }
};