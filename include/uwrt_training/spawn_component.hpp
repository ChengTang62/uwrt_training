#ifndef COMPOSITION_SPAWN_COMPONENT_HPP_
#define COMPOSITION_SPAWN_COMPONENT_HPP_

#include "uwrt_training/visibility_control.h"
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <turtlesim/srv/spawn.hpp>

namespace uwrt_training
{
    class spawn : public rclcpp::Node
    {
    private:
        rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr client_;
        rclcpp::TimerBase::SharedPtr timer_;

        void spawn_turtle();
    public:
        explicit spawn(const rclcpp::NodeOptions &options);
    };
}

#endif