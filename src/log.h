#ifndef LOG_H
#define LOG_H

#include <iostream>

#define LOG_TAG "IRCBot: "
#define LOG_ERROR(msg) std::cerr << LOG_TAG "error: " << msg << std::endl;
#define LOG_INFO(msg) std::cout << LOG_TAG "info: " << msg << std::endl;

#endif

