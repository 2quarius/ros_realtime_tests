cmake_minimum_required(VERSION 3.5)
project(communication_tests)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
   set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
   add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rt_tests_support REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
	msg/TimeStamp.msg
	DEPENDENCIES std_msgs
)

# catkin_package(CATKIN_DEPENDS roscpp std_msgs message_runtime rt_tests_support)

include_directories(../rt_tests_support/include)

add_executable(communication_tests_publisher
   ./src/Config.cpp
   ./src/Publisher.cpp
   ./src/ArgumentParser.cpp
   ./src/ct_publisher_node.cpp
)
rosidl_target_interfaces(communication_tests_publisher ${PROJECT_NAME} rosidl_typesupport_cpp)
ament_target_dependencies(communication_tests_publisher
	rclcpp
	rt_tests_support
)

add_executable(communication_tests_subscriber
   ./src/Config.cpp
   ./src/Subscriber.cpp
   ./src/ArgumentParser.cpp
   ./src/ct_subscriber_node.cpp
)
rosidl_target_interfaces(communication_tests_subscriber ${PROJECT_NAME} rosidl_typesupport_cpp)
ament_target_dependencies(communication_tests_subscriber
	rclcpp
	rt_tests_support
)

add_executable(bypass_node
   ./src/bypass_node.cpp
)
rosidl_target_interfaces(bypass_node ${PROJECT_NAME} rosidl_typesupport_cpp)
ament_target_dependencies(bypass_node
	rclcpp
	rt_tests_support
)

install(DIRECTORY launch
   DESTINATION share/${PROJECT_NAME}
)

install(TARGETS communication_tests_publisher communication_tests_subscriber bypass_node
   ARCHIVE DESTINATION lib/${PROJECT_NAME}
   LIBRARY DESTINATION lib/${PROJECT_NAME}
   RUNTIME DESTINATION bin/${PROJECT_NAME}
)

ament_package()
