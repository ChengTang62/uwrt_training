#ifndef COMPOSITION_RESET_TURTLE_HPP_
#define COMPOSITION_RESET_TURTLE_HPP_

#include <cstdlib>
#include <functional>
#include <memory>

#include <rclcpp/rclcpp.hpp>

#include <custom_interfaces/srv/reset_message.hpp>
#include <uwrt_training/visibility_control.h>
#include <turtlesim/srv/teleport_absolute.hpp>

namespace uwrt_training
{
    class reset : public rclcpp::Node
    {
    public:
        explicit reset(const rclcpp::NodeOptions &options);

    private:
        rclcpp::Service<custom_interfaces::srv::ResetMessage>::SharedPtr service_;
        rclcpp::Client<turtlesim::srv::TeleportAbsolute>::SharedPtr client_;
        void service_callback(const std::shared_ptr<custom_interfaces::srv::ResetMessage::Request> request, std::shared_ptr<custom_interfaces::srv::ResetMessage::Response> response);
    };
}
#endif