#include "ros/ros.h"
#include <communication_tests/timestamp_msg.h>


int main(int argc, char* argv[])
{
    ros::init(argc, argv, "bypass");
    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<communication_tests::timestamp_msg>("communication_test", 1000);
    int cnt = 0;
    ros::Subscriber sub = n.subscribe<communication_tests::timestamp_msg>("bypass", 1000,
        [&](const communication_tests::timestamp_msg::ConstPtr& msg)
        {
            ROS_INFO("recieve %d th msg", cnt);
            pub.publish(*msg);
            cnt++;
        });
    ros::spin();
}