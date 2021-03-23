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
	rosPublisher(nodeHandle->create_publisher<communication_tests::msg::TimeStamp>(topic, 1000))
{
	Config* config = Config::getConfig();
	message.payload.clear();
	for(int i = 0; i < config->payloadLength; i++)
	{
		message.payload.push_back(0xFF);
	}
	timer = nodeHandle->create_wall_timer(1000ms / config->pubFrequency, 
		[&](){
			message.seq = sequenceNumber;
			message.last_msg = (sequenceNumber == (config->amountMessages-1));
			struct timespec ts;
			clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
			message.sec = ts.tv_sec;
			message.nsec = ts.tv_nsec;
			rosPublisher->publish(message);			
			sequenceNumber++;
			RCLCPP_INFO(nodeHandle->get_logger(), 'pubed %d th msg', sequenceNumber);
			if(sequenceNumber == config->amountMessages) {
				timer->cancel();
				rclcpp::shutdown();
			}
		})
}

void Publisher::publish()
{
}

Publisher::~Publisher()
{
}
