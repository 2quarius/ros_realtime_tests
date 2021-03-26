/**
* Copyright (C) 2014, BMW Car IT GmbH
* Author: Jonas Sticha (Jonas.Sticha@bmw-carit.de)
*
* This software is licensed under BSD 3-clause License
* (see http://spdx.org/licenses/BSD-3-Clause).
**/

#include "Config.h"
#include "Publisher.h"
#include "ArgumentParser.h"
#include <rt_tests_support/Logger.h>
#include <rt_tests_support/PrioritySwitcher.h>
#include <thread>
#include <chrono>

int main(int argc, char* argv[])
{
	rclcpp::init(argc, argv);
	Config* config = Config::getConfig();
	ArgumentParser argParser;
	if(!argParser.parseArgs(argc, argv))
	{
		argParser.printUsage();
		return 1;
	}
	if(config->rtPrio)
	{
		PrioritySwitcher prioSwitcher(config->fifoScheduling);
		if(prioSwitcher.switchToRealtimePriority() != 0)
		{
			Logger::ERROR("Switching to realtime priority failed, maybe not running as root?");
			return 1;
		}
	}
	config->nodeHandle = rclcpp::Node::make_shared("communication_tests_publisher");
	Publisher publisher(config->topic);
	RCLCPP_INFO(config->nodeHandle->get_logger(), "%d", config->amountMessages);
	std::this_thread::sleep_for(std::chrono::seconds(config->startDelay));
	rclcpp::spin(config->nodeHandle);
	Logger::INFO("Done publishing...");
	return 0;
}
