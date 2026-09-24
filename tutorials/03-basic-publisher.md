# Basic Publisher

The following is a very basic example of a ROS 2 Node. We will go through each key part. Before the breakdown, 
Copy the following code into `src/my_package/src/publisher.cpp` and compile using
```bash
colcon build 
```

<details>
<summary><b>Basic Publisher Node</b></summary>

```c++
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class MyPublisher : public rclcpp::Node {
public:
  MyPublisher() : Node{"my_publisher_node"}, m_count{0} {
    m_publisher = this->create_publisher<std_msgs::msg::String>(
        "topic", rclcpp::QoS(rclcpp::KeepLast(10)));
    m_timer = this->create_wall_timer(std::chrono::milliseconds(500),
                                      [this] { this->timer_callback(); });
  }

private:
  auto timer_callback() -> void {
    auto message = std_msgs::msg::String{};
    message.data = "Hello world! " + std::to_string(this->m_count++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    this->m_publisher->publish(message);
  }

  size_t m_count;
  rclcpp::TimerBase::SharedPtr m_timer;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr m_publisher;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MyPublisher>());
  rclcpp::shutdown();
  return 0;
}
```
</details>

## Code breakdown

ROS 2 C++ nodes inherit from `rclcpp::Node`. The argument to the `rclcpp::Node` constructor is the name of the node as seen by `ros2 node list` command.

This line right here is what creates the publisher on the topic `"topic"`. 
```c++
    m_publisher = this->create_publisher<std_msgs::msg::String>(
        "topic", rclcpp::QoS(rclcpp::KeepLast(10)));
```
The template parameter `std_msgs::msg::String` is the type of the messages published to the topic. There are many packages with many types of messages. You can define your own message types.

The second parameter is the topic name as a string.

`rclcpp::QoS(rclcpp::KeepLast(10))` configures the Quality of Service of the topic. In this case we are saying to keep an internal buffer of the last 10 messages.
There are other configuration options for QoS you can read about [here](https://docs.ros.org/en/jazzy/Concepts/Intermediate/About-Quality-of-Service-Settings.html).

The following line creates a timer that runs a lambda every 500ms, which in turn only calls `timer_callback`.
```c++
    m_timer = this->create_wall_timer(std::chrono::milliseconds(500),
                                      [this] { this->timer_callback(); });
```

`timer_callback` is a simple function that creates a `std_msgs::msg::String`, logs it using ROS logging macros, and the publisher it to the topic.

`main` contains the basic ROS 2 boilerplate for running a single node.

## Running the node

Before running the node, always remember to do 2 things.

1. Compile the most recent version.
2. `source install/setup.bash`

If everything has gone well, you should be able to run:
```bash
ros2 run my_package my_publisher_node
```
Where `my_package` is the name of the package and `my_publisher_node` is the name of the executable.
