#include <memory>
#include <uwrt_training/spawn_component.hpp>

using namespace std::chrono_literals;

namespace uwrt_training
{
    spawn::spawn(const rclcpp::NodeOptions &options) : Node("spawn", options)
    {
        client_ = this->create_client<turtlesim::srv::Spawn>("/spawn");
        timer_ = this->create_wall_timer(5s, std::bind(&spawn::spawn_turtle, this));
    }

    void spawn::spawn_turtle()
    {
        if (!client_->wait_for_service(1s))
        {
            if (!rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(), "error");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "waiting");
            return;
        }

        std::unique_ptr<turtlesim::srv::Spawn::Request> request_stationary = std::make_unique<turtlesim::srv::Spawn::Request>();
        std::unique_ptr<turtlesim::srv::Spawn::Request> request_moving = std::make_unique<turtlesim::srv::Spawn::Request>();
        request_stationary->name = "stationary_turtle";
        request_stationary->x = 5;
        request_stationary->y = 5;
        request_stationary->theta = 0;
        request_stationary->name = "moving_turtle";
        request_moving->x = 25;
        request_moving->y = 10;
        request_moving->theta = 0;

        auto callback = [this](rclcpp::Client<turtlesim::srv::Spawn>::SharedFuture response) -> void
        {
            RCLCPP_INFO(this->get_logger(), "Created");
            // rclcpp::shutdown();
        };

        auto result_stationary = client_->async_send_request(std::move(request_stationary), callback);
        auto result_moving = client_->async_send_request(std::move(request_moving), callback);
    }
}
#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(uwrt_training::spawn)