#include "my_components/publisher_component.hpp"
#include <chrono>
#include <memory>
#include <utility>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;
namespace my_components
{
    publisherNode::publisherNode(const rclcpp::NodeOptions &options) : Node("publisher", options)
    {
        pub_ = create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        timer_ = create_wall_timer(1s, std::bind(&publisherNode::on_timer, this));
    }

    void publisherNode::on_timer()
    {
        auto msg = std::make_unique<geometry_msgs::msg::Twist>();
        msg->linear.x = 0.3;
        msg->angular.z = 0.3;
        std::flush(std::cout);

        pub_->publish(std::move(msg));
    }
}

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(my_components::publisherNode)