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
	auto n = rclcpp::Node::make_shared("communication_tests_subscriber");
	auto sub = n->create_subscription<communication_tests::msg::TimeStamp>(config->topic, rclcpp::QoS(1000).best_effort().durability_volatile(),
		[&](const communication_tests::msg::TimeStamp::SharedPtr msg){
			RCLCPP_INFO(n->get_logger(), "received %d th msg", msg->seq);
		});
	// RCLCPP_INFO(config->nodeHandle->get_logger(), "init subscriber");
	// Subscriber subscriber(config->topic);
	// RCLCPP_INFO(config->nodeHandle->get_logger(), "start spin");
	rclcpp::spin(n);
	// RCLCPP_INFO(config->nodeHandle->get_logger(), "start measure");
	// subscriber.startMeasurement();
	// subscriber.printMeasurementResults();
	// subscriber.saveGnuplotData();
	return 0;
}
