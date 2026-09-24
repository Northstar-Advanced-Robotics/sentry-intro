cmake_minimum_required(VERSION 3.8)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(my_package)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(my_publisher_node
  src/publisher.cpp
)
target_link_libraries(my_publisher_node
PUBLIC
  rclcpp::rclcpp
  std_msgs::std_msgs
)

add_executable(my_listener_node
  src/listener.cpp
)

target_link_libraries(my_listener_node
PUBLIC
  rclcpp::rclcpp
  std_msgs::std_msgs
)

install(TARGETS
  my_publisher_node
  my_listener_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
