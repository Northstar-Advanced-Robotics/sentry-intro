#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class MyListener : public rclcpp::Node {
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr m_subscription;

  void message_callback(const std_msgs::msg::String &msg) {
    RCLCPP_INFO(this->get_logger(), "Recieved message {%s}'", msg.data.c_str());
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
