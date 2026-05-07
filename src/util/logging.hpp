#pragma once

#include <functional>

void printHelp();

int logAndHandleErrors(std::function<void()> function);
