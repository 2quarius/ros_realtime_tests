/**
* Copyright (C) 2014, BMW Car IT GmbH
* Author: Jonas Sticha (Jonas.Sticha@bmw-carit.de)
*
* This software is licensed under BSD 3-clause License
* (see http://spdx.org/licenses/BSD-3-Clause).
**/

#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include <rclcpp/rclcpp.hpp>
#include <string>
#include "communication_tests/msg/time_stamp.hpp"

class Publisher {
public:
	Publisher(const std::string& topic);
	void publish();
	~Publisher();
private:
	Publisher();
	rclcpp::Node::SharedPtr nodeHandle;
	rclcpp::Publisher<communication_tests::msg::TimeStamp>::SharedPtr rosPublisher;
};

#endif //PUBLISHER_H_
