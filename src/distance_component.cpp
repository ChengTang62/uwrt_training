#include <cmath>
#include <iostream>
#include <string>
#include "my_components/distance_component.hpp"
#include <chrono>
#include <memory>
#include <utility>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;
namespace my_components
{
    distance::distance(const rclcpp::NodeOptions &options) : Node("distance", options)
    {
        auto callback_moving =
            [this](const typename turtlesim::msg::Pose::SharedPtr msg) -> void
        {
            this->moving_x = msg->x;
            this->moving_y = msg->y;
            std::flush(std::cout);
        };
        auto callback_stationary =
            [this](const typename turtlesim::msg::Pose::SharedPtr msg) -> void
        {
            this->stationary_x = msg->x;
            this->stationary_y = msg->y;
            std::flush(std::cout);
        };
        pub_ = create_publisher<my_components::msg::DistanceMessage>("/distance", 10);
        timer_ = create_wall_timer(1s, std::bind(&distance::on_timer, this));
        moving_sub_ = create_subscription<turtlesim::msg::Pose>("/moving_turtle/pose", 10, callback_moving);
        stationary_sub_ = create_subscription<turtlesim::msg::Pose>("/stationary_turtle/pose", 10, callback_stationary);
    }

    void distance::on_timer()
    {
        double diff_x{abs(this->stationary_x - this->moving_x)};
        double diff_y{abs(this->stationary_y - this->moving_y)};

        auto msg = std::make_unique<my_components::msg::DistanceMessage>();
        if (diff_x && diff_y)
        {
            msg->x = diff_x;
            msg->y = diff_y;
            msg->total = sqrt((diff_x * diff_x) + (diff_y * diff_y));
        }else{
            msg->x = 0;
            msg->y = 0;
            msg->total = 0;
        }
        this->pub_->publish(std::move(msg));
        std::flush(std::cout);
    }
}

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(my_components::distance)