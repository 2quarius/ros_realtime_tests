/**
* Copyright (C) 2014, BMW Car IT GmbH
* Author: Jonas Sticha (Jonas.Sticha@bmw-carit.de)
*
* This software is licensed under BSD 3-clause License
* (see http://spdx.org/licenses/BSD-3-Clause).
**/

#ifndef CONFIG_H_
#define CONFIG_H_

#include "ros/ros.h"
#include <string>
#include <rt_tests_support/PrioritySwitcher.h>

class Config {
public:
	static Config* getConfig();
	std::string getFilename();
	std::string getTitle();
	ros::NodeHandle* nodeHandle;
	bool rtPrio;
	bool fifoScheduling;
	int startDelay;
	int pubFrequency;
	int payloadLength;
	int amountMessages;
	std::string namePrefix;
	std::string topic;
private:
	Config();
	~Config();
	Config(const Config&);
	static Config* configInstance;
};

#endif //CONFIG_H_
