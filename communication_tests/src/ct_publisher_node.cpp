/**
* Copyright (C) 2014, BMW Car IT GmbH
* Author: Jonas Sticha (Jonas.Sticha@bmw-carit.de)
*
* This software is licensed under BSD 3-clause License
* (see http://spdx.org/licenses/BSD-3-Clause).
**/

#include <rt_tests_support/Logger.h>
#include <thread>
#include <chrono>
#include "communication_tests/msg/time_stamp.hpp"
#include "rclcpp/rclcpp.hpp"
#include "Config.h"

using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
	rclcpp::init(argc, argv);
	Config* config = Config::getConfig();
	if(!parse_argument(argc, argv, config)) {
		return 1;
	}
	auto n = rclcpp::Node::make_shared("communication_tests_publisher");
	// construct msg
	auto message = communication_tests::msg::TimeStamp();
	message.payload.clear();
	for(size_t i = 0; i < config->payload; i++)
	{
		message.payload.push_back(0xFF);
	}
	// publish msg
	size_t sequenceNumber = 0;
	auto pub = n->create_publisher<communication_tests::msg::TimeStamp>(config->topic, rclcpp::QoS(1000).best_effort().durability_volatile());
	rclcpp::TimerBase::SharedPtr timer = n->create_wall_timer(1000ms / config->freq,
		[&](){
			message.seq = sequenceNumber;
			message.last_msg = (sequenceNumber == (config->rep - 1));
			struct timespec ts;
			clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
			message.sec = ts.tv_sec;
			message.nsec = ts.tv_nsec;
			pub->publish(message);
			sequenceNumber++;
			RCLCPP_INFO(n->get_logger(), "seq : %d, total : %d", sequenceNumber, config->rep);
			if(sequenceNumber == config->rep) {
				timer->cancel();
				rclcpp::shutdown();
			}
		});
	RCLCPP_INFO(n->get_logger(), "%d", config->rep);
	std::this_thread::sleep_for(std::chrono::seconds(config->delay));
	rclcpp::spin(n);
	Logger::INFO("Done publishing...");
	return 0;
}
