/**
* Copyright (C) 2014, BMW Car IT GmbH
* Author: Jonas Sticha (Jonas.Sticha@bmw-carit.de)
*
* This software is licensed under BSD 3-clause License
* (see http://spdx.org/licenses/BSD-3-Clause).
**/

#include "Config.h"
#include <rt_tests_support/Logger.h>

int main(int argc, char* argv[])
{
	Config* config = Config::getConfig();
	if(!parse_argument(argc, argv, config)) {
		return 1;
	}
	rclcpp::init(argc, argv);
	auto n = rclcpp::Node::make_shared("communication_tests_subscriber");
	n->create_subscription<communication_tests::msg::TimeStamp>(config->topic, 1000,
		[&](const communication_tests::msg::TimeStamp::SharedPtr msg){
			RCLCPP_INFO(n->get_logger(), "received %d th msg", msg->seq);
		});
	// RCLCPP_INFO(config->nodeHandle->get_logger(), "init subscriber");
	// Subscriber subscriber(config->topic);
	// RCLCPP_INFO(config->nodeHandle->get_logger(), "start spin");
	// rclcpp::spin(config->nodeHandle);
	// RCLCPP_INFO(config->nodeHandle->get_logger(), "start measure");
	// subscriber.startMeasurement();
	// subscriber.printMeasurementResults();
	// subscriber.saveGnuplotData();
	return 0;
}
