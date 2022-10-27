#ifndef COMPOSITION__MOVE_COMPONENT_HPP_
#define COMPOSITION__MOVE_COMPONENT_HPP_

#include <chrono>
#include <functional>
#include <memory>
#include <thread>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <my_components/action/software.hpp>
#include "my_components/visibility_control.h"
#include <geometry_msgs/msg/twist.hpp>
#include <turtlesim/msg/pose.hpp>

namespace my_components
{

    class Move : public rclcpp::Node
    {

    public:
        explicit Move(const rclcpp::NodeOptions &options);
        using Move = my_components::action::Move;
        using GoalHandleMove =
            rclcpp_action::GoalHandle<Move>;

    private:
        static float linear_vel;
        static float angular_vel;
        static float x;
        static float y;
        static float angle;
        rclcpp_action::Server<Move>::SharedPtr
            action_server;
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
        rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub_;
        rclcpp_action::GoalResponse handle_goal(
            const rclcpp_action::GoalUUID &uuid,
            std::shared_ptr<const Move::Goal> goal);
        rclcpp_action::CancelResponse
        handle_cancel(const std::shared_ptr<GoalHandleMove> goal_handle);
        void
        handle_accepted(const std::shared_ptr<GoalHandleMove> goal_handle);
        void execute(const std::shared_ptr<GoalHandleMove> goal_handle);
    };

}

#endif // MOVING_TURTLE_ACTION_SERVER_HPP_