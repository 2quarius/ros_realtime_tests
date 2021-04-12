/**
* Copyright (C) 2014, BMW Car IT GmbH
* Author: Jonas Sticha (Jonas.Sticha@bmw-carit.de)
*
* This software is licensed under BSD 3-clause License
* (see http://spdx.org/licenses/BSD-3-Clause).
**/

#include "Config.h"
#include <rt_tests_support/Logger.h>
#include "communication_tests/msg/time_stamp.hpp"

int main(int argc, char* argv[])
{
	rclcpp::init(argc, argv);
	Config* config = Config::getConfig();
	if(!parse_argument(argc, argv, config)) {
		return 1;
	}
	config->node = rclcpp::Node::make_shared("communication_tests_subscriber");
	Subscriber subscriber(config->topic);
	subscriber.startMeasurement();
	subscriber.printMeasurementResults();
	subscriber.saveGnuplotData();
	return 0;
}
