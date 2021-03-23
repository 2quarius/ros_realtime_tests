cmake_minimum_required(VERSION 3.5)
project(rt_tests_support)

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

include_directories(./include)

add_library(${PROJECT_NAME}_lib STATIC
   ../rt_tests_support/src/Logger.cpp
   ../rt_tests_support/src/PrioritySwitcher.cpp
   ../rt_tests_support/src/PlotDataFileCreator.cpp
   ../rt_tests_support/src/MeasurementDataEvaluator.cpp
)

install(TARGETS ${PROJECT_NAME}_lib
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   RUNTIME DESTINATION bin
)

install(DIRECTORY include/${PROJECT_NAME}
   DESTINATION install
)

ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME}_lib)
ament_package()
