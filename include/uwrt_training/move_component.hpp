#ifndef COMPOSITION__MOVE_COMPONENT_HPP_
#define COMPOSITION__MOVE_COMPONENT_HPP_

#include <chrono>
#include <functional>
#include <memory>
#include <thread>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <custom_interfaces/action/move.hpp>
#include "uwrt_training/visibility_control.h"
#include <geometry_msgs/msg/twist.hpp>
#include <turtlesim/msg/pose.hpp>

namespace uwrt_training
{

    class Move : public rclcpp::Node
    {

    public:
        explicit Move(const rclcpp::NodeOptions &options);
        using MoveTurtle = custom_interfaces::action::Move;
        using GoalHandleMove =
            rclcpp_action::ServerGoalHandle<MoveTurtle>;

    private:
        float linear_vel;
        float angular_vel;
        float x;
        float y;
        float angle;
        float goal_angle;
        rclcpp_action::Server<MoveTurtle>::SharedPtr
            action_server;
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
        rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub_;
        rclcpp_action::GoalResponse handle_goal(
            const rclcpp_action::GoalUUID &uuid,
            std::shared_ptr<const MoveTurtle::Goal> goal);
        rclcpp_action::CancelResponse
        handle_cancel(const std::shared_ptr<GoalHandleMove> goal_handle);
        void
        handle_accepted(const std::shared_ptr<GoalHandleMove> goal_handle);
        void execute(const std::shared_ptr<GoalHandleMove> goal_handle);
    };
}

#endif // MOVING_TURTLE_ACTION_SERVER_HPP_





// #ifndef COMPOSITION_MOVE_HPP_
// #define COMPOSITION_MOVE_HPP_
// #include <memory>
// #include <rclcpp/rclcpp.hpp>
// #include <custom_interfaces/msg/distance_message.hpp>
// #include <turtlesim/msg/pose.hpp>
// namespace uwrt_training
// {
//     class Move : public rclcpp::Node
//     {
//     private:
//         rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub_;
//         rclcpp::Publisher<custom_interfaces::msg::DistanceMessage>::SharedPtr pub_;
//         rclcpp::TimerBase::SharedPtr timer_;

//         float x;
//         float y;

//     protected:
//         void on_timer();

//     public:
//         explicit Move(const rclcpp::NodeOptions &options);
//     };
// }

// #endif 

