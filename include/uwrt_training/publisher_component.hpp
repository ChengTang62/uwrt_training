#ifndef COMPOSITION_PUBLISHER_COMPONENT_HPP_
#define COMPOSITION_PUBLISHER_COMPONENT_HPP_

#include "uwrt_training/visibility_control.h"
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

namespace uwrt_training
{
    class publisherNode : public rclcpp::Node
    {
    public:
        COMPOSITION_PUBLIC
        explicit publisherNode(const rclcpp::NodeOptions &options);
    protected:
        void on_timer();
    private:
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
        rclcpp::TimerBase::SharedPtr timer_;
    };

} // namespace composition

#endif // COMPOSITION_PUBLISHER_COMPONENT_HPP_