/**
* Copyright (C) 2014, BMW Car IT GmbH
* Author: Jonas Sticha (Jonas.Sticha@bmw-carit.de)
*
* This software is licensed under BSD 3-clause License
* (see http://spdx.org/licenses/BSD-3-Clause).
**/

#ifndef SUBSCRIBER_H_
#define SUBSCRIBER_H_

#include "Config.h"
#include <rclcpp/rclcpp.hpp>
#include <string>
#include <communication_tests/msg/time_stamp.hpp>
#include <rt_tests_support/MeasurementDataEvaluator.h>

class Subscriber{
public:
	Subscriber(const std::string& topic);
	void startMeasurement();
	void printMeasurementResults();
	void saveGnuplotData();
	int getAmountMessagesOutOfOrder();
	MeasurementDataEvaluator* getMeasurementData();
	~Subscriber();
private:
	Subscriber();
	Config* config;
	int lastSeq;
	int outOfOrderCounter;
	const int amountMessages;
	const static int messageMissing = -1;
	rclcpp::Subscription<communication_tests::msg::TimeStamp>::SharedPtr rosSubscriber;
	MeasurementDataEvaluator* measurementData;
	std::string getMeasurementSummary();
	void messageCallback(const communication_tests::msg::TimeStamp::SharedPtr msg);
};

#endif //SUBSCRIBER_H_
