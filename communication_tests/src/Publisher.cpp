/**
* Copyright (C) 2014, BMW Car IT GmbH
* Author: Jonas Sticha (Jonas.Sticha@bmw-carit.de)
*
* This software is licensed under BSD 3-clause License
* (see http://spdx.org/licenses/BSD-3-Clause).
**/

#include "Config.h"
#include "Publisher.h"
#include <rt_tests_support/Logger.h>
#include <chrono>

using namespace std::chrono_literals;

Publisher::Publisher(const std::string& topic) :
	nodeHandle(Config::getConfig()->nodeHandle),
	rosPublisher(nodeHandle->create_publisher<communication_tests::msg::TimeStamp>(topic, rclcpp::QoS(1000).best_effort().durability_volatile()))
{
	Config* config = Config::getConfig();
	message.payload.clear();
	for(int i = 0; i < config->payload; i++)
	{
		message.payload.push_back(0xFF);
	}
	msgAmount = config->rep;
	timer = nodeHandle->create_wall_timer(1000ms / config->freq, 
		[&](){
			message.seq = sequenceNumber;
			message.last_msg = (sequenceNumber == (msgAmount-1));
			struct timespec ts;
			clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
			message.sec = ts.tv_sec;
			message.nsec = ts.tv_nsec;
			rosPublisher->publish(message);			
			sequenceNumber++;
			RCLCPP_INFO(nodeHandle->get_logger(), "seq : %d, total : %d", sequenceNumber, msgAmount);
			if(sequenceNumber == msgAmount) {
				timer->cancel();
				rclcpp::shutdown();
			}
		});
}

void Publisher::publish()
{
}

Publisher::~Publisher()
{
}
