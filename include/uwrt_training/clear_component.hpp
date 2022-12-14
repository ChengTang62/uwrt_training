#ifndef COMPOSITION_CLEAR_COMPONENT_HPP_
#define COMPOSITION_CLEAR_COMPONENT_HPP_
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include <rclcpp/rclcpp.hpp>
#include "uwrt_training/visibility_control.h"
#include <turtlesim/srv/kill.hpp>

namespace uwrt_training
{
    class clear : public rclcpp :: Node
    {
    public:
        explicit clear(const rclcpp::NodeOptions &options);
    private:
        rclcpp::Client<turtlesim::srv::Kill>::SharedPtr client_;
        rclcpp::TimerBase::SharedPtr timer_;
        void clear_turtle();
    };
}

#endif