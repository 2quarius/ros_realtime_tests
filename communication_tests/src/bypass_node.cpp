#include <communication_tests/msg/timestamp.hpp>
#include <rclcpp/rclcpp.hpp>

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::Node::SharedPtr n = rclcpp::Node::make_shared("bypass");

    rclcpp::Publisher<communication_tests::timestamp_msg>::SharedPtr pub = n->create_publisher<communication_tests::timestamp_msg>("communication_test", 1000);
    int cnt = 0;
    rclcpp::Subscription<communication_tests::timestamp_msg>::SharedPtr sub = n->create_subscription<communication_tests::timestamp_msg>("bypass", 1000,
        [&](const communication_tests::timestamp_msg::ConstPtr& msg)
        {
            RCLCPP_INFO(n->get_logger(), "recieve %d th msg", cnt);
            pub->publish(*msg);
            cnt++;
        });
    rclcpp::spin(n);
}