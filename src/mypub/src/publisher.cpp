#include <format>
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
    message.data = std::format("Hello world! {}\n", this->m_count++);
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
