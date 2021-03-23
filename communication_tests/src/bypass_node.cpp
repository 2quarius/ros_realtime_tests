#include <communication_tests/msg/time_stamp.hpp>
#include <rclcpp/rclcpp.hpp>

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::Node::SharedPtr n = rclcpp::Node::make_shared("bypass");

    rclcpp::Publisher<communication_tests::msg::TimeStamp>::SharedPtr pub = n->create_publisher<communication_tests::msg::TimeStamp>("communication_test", 1000);
    int cnt = 0;
    rclcpp::Subscription<communication_tests::msg::TimeStamp>::SharedPtr sub = n->create_subscription<communication_tests::msg::TimeStamp>("bypass", 1000,
        [&](const communication_tests::msg::TimeStamp::SharedPtr msg)
        {
            RCLCPP_INFO(n->get_logger(), "recieve %d th msg", cnt);
            pub->publish(*msg);
            cnt++;
        });
    rclcpp::spin(n);
}