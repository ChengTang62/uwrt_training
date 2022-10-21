#include <chrono>
#include <my_components/reset_component.hpp>

using namespace std::chrono_literals;
using namespace std::placeholders;

namespace my_components
{
    reset::reset(const rclcpp::NodeOptions &options) : Node("reset", options)
    {
        client_ = this->create_client<turtlesim::srv::TeleportAbsolute>("/moving_turtle/teleport_absolute");
        service_ = this->create_service<my_components::srv::ResetMessage>("/reset_moving_turtle",std::bind(&reset::service_callback, this, _1, _2));
    }
    void reset::service_callback(
        const std::shared_ptr<my_components::srv::ResetMessage::Request> request,
        std::shared_ptr<my_components::srv::ResetMessage::Response> response)
    {
        if (!client_->wait_for_service(1s))
        {
            if (!rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(), "error");
                response->success = false;
                return;
            }
            RCLCPP_INFO(this->get_logger(), "timeout");
            response->success = false;
            return;
        }
        auto client_request=std::make_shared<turtlesim::srv::TeleportAbsolute::Request>();
        client_request->x=2;
        client_request->y=2;
        client_request->theta=0;
        auto response_callback=[this](rclcpp::Client<turtlesim::srv::TeleportAbsolute>::SharedFuture future)->void{
            RCLCPP_INFO(this->get_logger(), "Reseted");
        };
        auto result=client_->async_send_request(client_request, response_callback);
        response->success=true;
    }
}
#include <rclcpp_components/register_node_macro.hpp>

RCLCPP_COMPONENTS_REGISTER_NODE(my_components::reset)