#ifndef COMPOSITION_DISTANCE_HPP_
#define COMPOSITION_DISTANCE_HPP_
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <my_components/msg/distance_message.hpp>
#include <turtlesim/msg/pose.hpp>
namespace my_components
{
    class distance : public rclcpp::Node
    {
    private:
        rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr stationary_sub_;
        rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr moving_sub_;

        rclcpp::Publisher<my_components::msg::DistanceMessage>::SharedPtr pub_;
        rclcpp::TimerBase::SharedPtr timer_;

        float stationary_x;
        float stationary_y;
        float moving_x;
        float moving_y;
    protected:
        void on_timer();

    public:
        explicit distance(const rclcpp::NodeOptions &options);
    };
} // namespace my_components

#endif 