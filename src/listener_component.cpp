#include "my_components/listener_component.hpp"

#include <iostream>
#include <chrono>
#include <memory>
#include <utility>
// #include "geometry_msgs/msg/twist.hpp"
// #include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

namespace my_components
{
  Listener::Listener(const rclcpp::NodeOptions &options)
      : Node("listener", options)
  {
    auto callback =
        [this](const typename geometry_msgs::msg::Twist::SharedPtr msg) -> void
    {
      RCLCPP_INFO(this->get_logger(), "I heard: [%f]", msg->linear.x);
      std::flush(std::cout);
    };

    sub_ = create_subscription<geometry_msgs::msg::Twist>("chatter", 10, callback);
  }

} // namespace composition

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(my_components::Listener)
