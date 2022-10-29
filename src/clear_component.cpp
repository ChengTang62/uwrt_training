#include <uwrt_training/clear_component.hpp>
using namespace std::chrono_literals;

namespace uwrt_training
{
    clear::clear(const rclcpp::NodeOptions &options) : Node("clear", options)
    {
        client_ = this->create_client<turtlesim::srv::Kill>("/kill");
        timer_ = this->create_wall_timer(2s, std::bind(&clear::clear_turtle, this));
    }
    void clear::clear_turtle()
    {
        if (!client_->wait_for_service(2s))
        {
            if (!rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(), "error");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "waiting");
            return;
        }
        auto request1 = std::make_shared<turtlesim::srv::Kill::Request>();
        auto request2 = std::make_shared<turtlesim::srv::Kill::Request>();
        auto request3 = std::make_shared<turtlesim::srv::Kill::Request>();

        request1->name = "turtle1";
        request2->name = "moving_turtle";
        request3->name = "stationary_turtle";

        auto callback = [this](rclcpp::Client<turtlesim::srv::Kill>::SharedFuture response) -> void
        {
            (void)response;
            RCLCPP_INFO(this->get_logger(), "killed");
        };
        auto result1 = client_->async_send_request(request1, callback);
        auto result2 = client_->async_send_request(request2, callback);
        auto result3 = client_->async_send_request(request3, callback);
    }
}
#include <rclcpp_components/register_node_macro.hpp>

RCLCPP_COMPONENTS_REGISTER_NODE(uwrt_training::clear)
