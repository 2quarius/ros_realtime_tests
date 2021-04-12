/**
* Copyright (C) 2014, BMW Car IT GmbH
* Author: Jonas Sticha (Jonas.Sticha@bmw-carit.de)
*
* This software is licensed under BSD 3-clause License
* (see http://spdx.org/licenses/BSD-3-Clause).
**/

#include "Config.h"
#include <string>
#include <boost/program_options.hpp>
#include <iostream>

Config* Config::configInstance = 0;

Config* Config::getConfig()
{
	if(configInstance == 0)
	{
		configInstance = new Config();
	}
	return configInstance;
}

namespace po = boost::program_options;

bool parse_argument(int argc, char** argv, Config* config)
{
	po::options_description description("Usage");
	description.add_options()
		("help,h", "produce help message")
		("schedule,s", po::value<std::string>(&config->schedule)->default_value("0"), "scheduling policy")
		("repitition,r", po::value<int>(&config->rep)->default_value(1000), "repitition of message")
		("frequency,f", po::value<int>(&config->freq)->default_value(1000), "publish rate")
		("payload,l", po::value<size_t>(&config->payload)->defalut_value(0), "payload of messaage")
		("prefix,p", po::value<std::string>(&config->prefix)->default_value(""), "prefix name of log file")
		("delay,d", po::value<int>(&config->delay)->default_value(1), "time in second to delay before publish")
		("topic,t", po::value<std::string>(&config->topic)->default_value("communication_test"), "topic to publish message into")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, description), vm);
	po::notify(vm);

	if(vm.count("help")) {
		std::cout << description << "\n";
		return false;
	}
	return true;
}