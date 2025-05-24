#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "CommandWrapper.h"

void runCommandLoop(std::unordered_map<std::string, CommandWrapper>& commandMap);