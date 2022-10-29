#include <cmath>
#include <memory>
#include <uwrt_training/move_component.hpp>
#include <chrono>
#include <utility>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"
#include <custom_interfaces/action/move.hpp>

using namespace std::chrono_literals;
using namespace std::placeholders;
using MoveTurtle = custom_interfaces::action::Move;
using GoalHandleMove =
    rclcpp_action::ServerGoalHandle<MoveTurtle>;
namespace uwrt_training
{
    Move::Move(
        const rclcpp::NodeOptions &options)
        : Node("move", options)
    {
        this->action_server =
            rclcpp_action::create_server<MoveTurtle>(
                this, "move",
                std::bind(&Move::handle_goal, this, _1, _2),
                std::bind(&Move::handle_cancel, this, _1),
                std::bind(&Move::handle_accepted, this, _1));
        auto sub_callback =
            [this](const turtlesim::msg::Pose::SharedPtr msg) -> void
        {
            this->x = msg->x;
            this->y = msg->y;
            this->angle = msg->theta;
        };
        pub_ = create_publisher<geometry_msgs::msg::Twist>("/moving_turtle/cmd_vel", 10);
        this->sub_ = this->create_subscription<turtlesim::msg::Pose>(
            "/moving_turtle/pose", 10, sub_callback);
    }

    rclcpp_action::GoalResponse Move::handle_goal(
        const rclcpp_action::GoalUUID &uuid,
        std::shared_ptr<const MoveTurtle::Goal> goal)
    {
        RCLCPP_INFO(this->get_logger(), "Received goal request with x:%f y:%f", goal->x,
                    goal->y);
        (void)uuid;
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    rclcpp_action::CancelResponse Move::handle_cancel(
        const std::shared_ptr<GoalHandleMove> goal_handle)
    {
        RCLCPP_INFO(this->get_logger(), "Recieved request to cancel goal");
        (void)goal_handle;
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    void Move::handle_accepted(
        const std::shared_ptr<GoalHandleMove> goal_handle)
    {
        std::thread{std::bind(&Move::execute, this, _1),
                    goal_handle}
            .detach();
    }

    void Move::execute(
        const std::shared_ptr<GoalHandleMove> goal_handle)
    {
        RCLCPP_INFO(this->get_logger(), "Excuting goal");
        rclcpp::Time begin = this->now();
        const auto goal = goal_handle->get_goal();
        auto feedback = std::make_shared<MoveTurtle::Feedback>();
        auto &diff_x = feedback->dist_x;
        auto &diff_y = feedback->dist_y;
        auto result =
            std::make_unique<MoveTurtle::Result>();
        auto velocity = geometry_msgs::msg::Twist();
        rclcpp::Rate loop_rate{40};

        if ((goal->x - this->x) < 0 && (goal->y - this->y) < 0)
        {
            this->goal_angle = -3.14 + atan((goal->y - this->y) / (goal->x - this->x));
        }
        else if ((goal->x - this->x) < 0 && (goal->y - this->y) > 0)
        {
            this->goal_angle = 3.14 + atan((goal->y - this->y) / (goal->x - this->x));
        }
        else
        {
            this->goal_angle = atan((goal->y - this->y) / (goal->x - this->x));
        }
        RCLCPP_INFO(this->get_logger(), "Current x,y is:%f %f", x, y);

        RCLCPP_INFO(this->get_logger(), "Goal angle is:%f", goal_angle);

        while (rclcpp::ok())
        {
            if (goal_handle->is_canceling())
            {
                RCLCPP_INFO(this->get_logger(), "Goal canceled");
                rclcpp::Time end = this->now();
                rclcpp::Duration duration = end - begin;
                long int duration_nanosec{duration.nanoseconds()};
                result->duration = duration_nanosec;
                goal_handle->canceled(std::move(result));
                return;
            }
            diff_x = abs(this->x - goal->x);
            diff_y = abs(this->y - goal->y);
            if (angle < goal_angle - 0.005)
            {
                velocity.angular.z = 0.3;
                RCLCPP_INFO(this->get_logger(), "Turning Left");
                RCLCPP_INFO(this->get_logger(), "At angle:%f", angle);
            }
            else if (angle > goal_angle + 0.005)
            {
                velocity.angular.z = -0.3;
                RCLCPP_INFO(this->get_logger(), "Turning Right");
                RCLCPP_INFO(this->get_logger(), "At angle:%f", angle);
            }
            else
            {
                if (!((x < goal->x + 0.05) && (x > goal->x - 0.05) && (y < goal->y + 0.05) && (y > goal->y - 0.05)))
                {
                    RCLCPP_INFO(this->get_logger(), "At position:%f %f", this->x, this->y);
                    velocity.angular.z = 0;
                    velocity.linear.x = 0.3;
                }
                else
                {
                    break;
                }
            }
            pub_->publish(velocity);
            goal_handle->publish_feedback(feedback);
            loop_rate.sleep();
        }

        if (rclcpp::ok())
        {
            rclcpp::Time end = this->now();
            rclcpp::Duration duration = end - begin;
            long int duration_nanosec{duration.nanoseconds()};
            result->duration = duration_nanosec;
            result->duration = 10;

            goal_handle->succeed(
                std::move(result));
            RCLCPP_INFO(this->get_logger(), "Goal succeeded");
        }
    }

} // class Move

#include <rclcpp_components/register_node_macro.hpp>

RCLCPP_COMPONENTS_REGISTER_NODE(uwrt_training::Move)