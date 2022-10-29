cmake_minimum_required(VERSION 3.8)
project(uwrt_training)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(action_msgs REQUIRED)
find_package(composition REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(std_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(custom_interfaces REQUIRED)
find_package(rclcpp_action REQUIRED)

include_directories(include)

add_library(publisher_component SHARED src/publisher_component.cpp)
target_compile_definitions(publisher_component PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(publisher_component
  "rclcpp"
  "rclcpp_components"
  "geometry_msgs"
)

rclcpp_components_register_nodes(publisher_component "uwrt_training::publisherNode")
set(node_plugins "${node_plugins}uwrt_training::publisherNode;$<TARGET_FILE:publisher_component>\n")

add_library(spawn_component SHARED src/spawn_component.cpp)
target_compile_definitions(spawn_component PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(spawn_component
  "rclcpp"
  "rclcpp_components"
  "geometry_msgs"
  "turtlesim"
  "std_msgs"
)

rclcpp_components_register_nodes(spawn_component "uwrt_training::spawn")
set(node_plugins "${node_plugins}uwrt_training::spawn;$<TARGET_FILE:spawn_component>\n")


add_library(clear_component SHARED src/clear_component.cpp)
target_compile_definitions(clear_component PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(clear_component
  "rclcpp"
  "rclcpp_components"
  "geometry_msgs"
  "turtlesim"
  "std_msgs"
)

rclcpp_components_register_nodes(clear_component "uwrt_training::clear")
set(node_plugins "${node_plugins}uwrt_training::clear;$<TARGET_FILE:clear_component>\n")


add_library(reset_component SHARED src/reset_component.cpp)
target_compile_definitions(reset_component PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(reset_component
  "rclcpp"
  "rclcpp_components"
  "geometry_msgs"
  "turtlesim"
  "std_msgs"
  "custom_interfaces"
)

rclcpp_components_register_nodes(reset_component "uwrt_training::reset")
set(node_plugins "${node_plugins}uwrt_training::reset;$<TARGET_FILE:reset_component>\n")


add_library(distance_component SHARED src/distance_component.cpp)
target_compile_definitions(distance_component PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(distance_component
  "rclcpp"
  "rclcpp_components"
  "turtlesim"
  "std_msgs"
  "turtlesim"
  "custom_interfaces"
)

rclcpp_components_register_nodes(distance_component "uwrt_training::distance")
set(node_plugins "${node_plugins}uwrt_training::distance;$<TARGET_FILE:distance_component>\n")

add_library(move_component SHARED src/move_component.cpp)
target_compile_definitions(move_component PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(move_component
  "rclcpp"
  "rclcpp_components"
  "turtlesim"
  "std_msgs"
  "custom_interfaces"
  "rclcpp_action"
  "geometry_msgs"
)

rclcpp_components_register_nodes(move_component "uwrt_training::Move")
set(node_plugins "${node_plugins}uwrt_training::Move;$<TARGET_FILE:move_component>\n")


# Install launch files.
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)


install(TARGETS
  publisher_component
  reset_component
  clear_component
  spawn_component
  distance_component
  move_component
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
