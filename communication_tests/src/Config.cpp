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
#include <sstream>
#include <sys/utsname.h>

Config* Config::configInstance = 0;

Config* Config::getConfig()
{
	if(configInstance == 0)
	{
		configInstance = new Config();
	}
	return configInstance;
}

std::string Config::getFilename()
{
	std::stringstream filename;
	filename << namePrefix;
	filename << "ct_gnuplot_l" << amountMessages << "_fq" << pubFrequency;
	filename << "_pl" << payloadLength;
	if(rtPrio)
	{
		filename << "-tnRT";
		if(fifoScheduling)
		{
			filename << "FIFO";
		} else {
			filename << "RR";
		}
	}
	return filename.str();
}

std::string Config::getTitle()
{
	struct utsname unameResponse;
	int rc = uname(&unameResponse);
	std::stringstream machineName;
	if(rc == 0)
	{
		machineName << unameResponse.nodename << " " << unameResponse.sysname << " " << unameResponse.release;
	}
	std::stringstream ss;
	ss << "communication_tests plot " << machineName.str() << " -  " << amountMessages << " samples; ";
	ss << "payload length " << payloadLength;
	if(rtPrio)
	{
		ss << "; test node RT ";
		if(fifoScheduling)
		{
			ss << "FIFO";
		} else {
			ss << "RR";
		}
	}
	return ss.str();
}

namespace po = boost::program_options;

bool parse_argument(int argc, char** argv, Config* config)
{
	po::options_description description("Usage");
	description.add_options()
		("help,h", "produce help message")
		("schedule,s", po::value<std::string>(&config->schedule)->default_value("0"), "scheduling policy")
		("repitition,c", po::value<int>(&config->rep)->default_value(1000), "repitition of message")
		("frequency,f", po::value<int>(&config->freq)->default_value(1000), "publish rate")
		("payload,l", po::value<size_t>(&config->payload)->default_value(0), "payload of messaage")
		("prefix,p", po::value<std::string>(&config->prefix)->default_value(""), "prefix name of log file")
		("delay,d", po::value<int>(&config->delay)->default_value(1), "time in second to delay before publish")
		("topic,t", po::value<std::string>(&config->topic)->default_value("communication_test"), "topic to publish message into")
	;

	po::variables_map vm;
	po::store(po::command_line_parser(argc, argv).options(description).allow_unregistered().run(), vm);
	po::notify(vm);

	if(vm.count("help")) {
		std::cout << description << "\n";
		return false;
	}
	return true;
}
