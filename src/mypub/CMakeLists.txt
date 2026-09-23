cmake_minimum_required(VERSION 3.8)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(mypub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(publisher_node
  src/publisher.cpp
)

target_link_libraries(publisher_node
PUBLIC
  rclcpp::rclcpp
  std_msgs::std_msgs
)
target_compile_features(publisher_node PRIVATE cxx_std_20)

add_executable(listener_node
  src/listener.cpp
)

target_link_libraries(listener_node
PUBLIC
  rclcpp::rclcpp
  std_msgs::std_msgs
)
target_compile_features(listener_node PRIVATE cxx_std_20)

install(TARGETS
  publisher_node
  listener_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
