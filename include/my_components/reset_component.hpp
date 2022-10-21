#ifndef COMPOSITION_RESET_TURTLE_HPP_
#define COMPOSITION_RESET_TURTLE_HPP_

#include <cstdlib>
#include <functional>
#include <memory>

#include <rclcpp/rclcpp.hpp>

#include <my_components/srv/reset_message.hpp>
#include <my_components/visibility_control.h>
#include <turtlesim/srv/teleport_absolute.hpp>

namespace my_components
{
    class reset : public rclcpp::Node
    {
    public:
        explicit reset(const rclcpp::NodeOptions &options);

    private:
        rclcpp::Service<my_components::srv::ResetMessage>::SharedPtr service_;
        rclcpp::Client<turtlesim::srv::TeleportAbsolute>::SharedPtr client_;
        void service_callback(const std::shared_ptr<my_components::srv::ResetMessage::Request> request, std::shared_ptr<my_components::srv::ResetMessage::Response> response);
    };
}
#endif