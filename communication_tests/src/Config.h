/**
* Copyright (C) 2014, BMW Car IT GmbH
* Author: Jonas Sticha (Jonas.Sticha@bmw-carit.de)
*
* This software is licensed under BSD 3-clause License
* (see http://spdx.org/licenses/BSD-3-Clause).
**/

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <rclcpp/rclcpp.hpp>
#include <rt_tests_support/PrioritySwitcher.h>

class Config {
public:
	static Config* getConfig();
	int delay;
	int freq;
	size_t payload;
	int rep;
	std::string prefix;
	std::string topic;
	std::string schedule;
private:
	Config() {};
	~Config();
	Config(const Config&);
	static Config* configInstance;
};

bool parse_argument(int argc, char** argv, Config* config);

#endif //CONFIG_H_
