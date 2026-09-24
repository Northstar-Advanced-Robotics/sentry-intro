# Basic Listener

This tutorial introduces subscribing to ROS 2 topics. The following node listens to messages published on the `"topic"` topic and logs them to the console.

Copy the following code into `src/my_package/src/listener.cpp`:

<details>
<summary><b>Basic Listener Node</b></summary>

```cpp
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class MyListener : public rclcpp::Node {
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr m_subscription;

  void message_callback(const std_msgs::msg::String &msg) {
    RCLCPP_INFO(this->get_logger(), "Received message {%s}'", msg.data.c_str());
  }

public:
  MyListener() : Node{"my_listener_node"} {
    m_subscription = this->create_subscription<std_msgs::msg::String>(
        "topic", rclcpp::QoS(rclcpp::KeepLast(10)),
        [this](const std_msgs::msg::String &msg) -> void {
          this->message_callback(msg);
        });
  }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MyListener>());
  rclcpp::shutdown();
  return 0;
}
```
</details>

## Updating `CMakeLists.txt`

Before compiling, we need to update the build script to add the new executable to the package.
Follow the steps done in tutorial 2 but for `my_listener_node`, adjusting the arguments to functions when neccesary.

You can see the main changes needed below to check your work (or help if you are stuck).

<details>
<summary><b>`CMakeLists.txt` changes</b></summary>

```cmake
# Added these lines
add_executable(my_listener_node
  src/listener.cpp
)
target_link_libraries(my_listener_node
PRIVATE
  rclcpp::rclcpp
  std_msgs::std_msgs
)
# ...
# update install call to install target `my_listener_node` as well  
install(TARGETS
  my_publisher_node
  my_listener_node
  DESTINATION lib/${PROJECT_NAME}
)
```
</details>


## Code breakdown

The basic structure of the node is largely the same, the only difference being that we now have a subscriber rather than a publisher.

The `create_subscription` code is very similar to `create_publisher`, however we now pass a callback as the 3rd argument.
Unlike with a publisher where you decide at what point to publish, with a subscription you have to register a callback so the ROS 2 runtime knows what to run when it receives a message.
In this case the callback is a lambda that forwards to a member function.
Take note of the argument type of the lambda. You can get nasty compiler errors if you get that type wrong.
```c++
    m_subscription = this->create_subscription<std_msgs::msg::String>(
        "topic", rclcpp::QoS(rclcpp::KeepLast(10)),
        [this](const std_msgs::msg::String &msg) -> void {
          this->message_callback(msg);
        });
  
```

## Running the node

If everything has gone well, you should be able to run:
```bash
ros2 run my_package my_listener_node
```
You will also need to run `my_publisher_node` in a separate terminal so that it can listen to the topic
> NOTE: You need to `source install/setup.bash` in the new terminal as well.
