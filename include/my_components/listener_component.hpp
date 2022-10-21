#ifndef COMPOSITION__LISTENER_COMPONENT_HPP_
#define COMPOSITION__LISTENER_COMPONENT_HPP_

#include "my_components/visibility_control.h"
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

namespace my_components
{

  class Listener : public rclcpp::Node
  {
  public:
    COMPOSITION_PUBLIC
    explicit Listener(const rclcpp::NodeOptions &options);

  private:
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr sub_;
  };

} // namespace composition

#endif // COMPOSITION__LISTENER_COMPONENT_HPP_