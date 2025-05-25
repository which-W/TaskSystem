#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "../static/CommandWrapper.h"

void runloop(std::unordered_map<std::string, CommandWrapper>& commandMap);
void runCommandLoop(std::unordered_map<std::string, CommandWrapper>& commandMap);
void runVerificationLoop(std::unordered_map<std::string, CommandWrapper>& commandMap);