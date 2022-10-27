cmake_minimum_required(VERSION 3.8)
project(my_components)

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
find_package(rosidl_default_generators REQUIRED)
find_package(my_components REQUIRED)

include_directories(include)

add_library(publisher_component SHARED src/publisher_component.cpp)
target_compile_definitions(publisher_component PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(publisher_component
  "rclcpp"
  "rclcpp_components"
  "geometry_msgs"
)

rclcpp_components_register_nodes(publisher_component "my_components::publisherNode")
set(node_plugins "${node_plugins}my_components::publisherNode;$<TARGET_FILE:publisher_component>\n")


add_library(listener_component SHARED src/listener_component.cpp)
target_compile_definitions(listener_component PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(listener_component
  "rclcpp"
  "rclcpp_components"
  "geometry_msgs"
)

rclcpp_components_register_nodes(listener_component "my_components::Listener")
set(node_plugins "${node_plugins}my_components::Listener;$<TARGET_FILE:listener_component>\n")


add_library(spawn_component SHARED src/spawn_component.cpp)
target_compile_definitions(spawn_component PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(spawn_component
  "rclcpp"
  "rclcpp_components"
  "geometry_msgs"
  "turtlesim"
  "std_msgs"
)

rclcpp_components_register_nodes(spawn_component "my_components::spawn")
set(node_plugins "${node_plugins}my_components::spawn;$<TARGET_FILE:spawn_component>\n")


add_library(clear_component SHARED src/clear_component.cpp)
target_compile_definitions(clear_component PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(clear_component
  "rclcpp"
  "rclcpp_components"
  "geometry_msgs"
  "turtlesim"
  "std_msgs"
)

rclcpp_components_register_nodes(clear_component "my_components::clear")
set(node_plugins "${node_plugins}my_components::clear;$<TARGET_FILE:clear_component>\n")


add_library(reset_component SHARED src/reset_component.cpp)
target_compile_definitions(reset_component PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(reset_component
  "rclcpp"
  "rclcpp_components"
  "geometry_msgs"
  "turtlesim"
  "std_msgs"
  "my_components"
)

rclcpp_components_register_nodes(reset_component "my_components::reset")
set(node_plugins "${node_plugins}my_components::reset;$<TARGET_FILE:reset_component>\n")


add_library(distance_component SHARED src/distance_component.cpp)
target_compile_definitions(distance_component PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(distance_component
  "rclcpp"
  "rclcpp_components"
  "turtlesim"
  "std_msgs"
  "turtlesim"
  "my_components"
)

rclcpp_components_register_nodes(distance_component "my_components::distance")
set(node_plugins "${node_plugins}my_components::distance;$<TARGET_FILE:distance_component>\n")

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
  # listener_component
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

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/ResetMessage.srv"
  "msg/DistanceMessage.msg"
  "action/Move.action"
)

ament_package()



# cmake_minimum_required(VERSION 3.8)
# project(my_components)

# if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#   add_compile_options(-Wall -Wextra -Wpedantic)
# endif()

# # find dependencies
# find_package(ament_cmake REQUIRED)
# find_package(rclcpp REQUIRED)
# find_package(rclcpp_components REQUIRED)
# find_package(composition REQUIRED)
# find_package(geometry_msgs REQUIRED)
# find_package(turtlesim REQUIRED)
# find_package(rosidl_default_generators REQUIRED)
# include_directories(include)

# add_library(moverobot_component SHARED src/moverobot_component.cpp)
# target_compile_definitions(moverobot_component PRIVATE "COMPOSITION_BUILDING_DLL")
# ament_target_dependencies(moverobot_component
#   "rclcpp"
#   "rclcpp_components"
#   "geometry_msgs")
# rclcpp_components_register_nodes(moverobot_component "my_components::MoveRobot")
# set(node_plugins "${node_plugins}my_components::MoveRobot;$<TARGET_FILE:moverobot_component>\n")


# add_library(listener_component SHARED src/listener_component.cpp)
# target_compile_definitions(listener_component PRIVATE "COMPOSITION_BUILDING_DLL")
# ament_target_dependencies(listener_component
#   "rclcpp"
#   "rclcpp_components"
#   "geometry_msgs"
# )

# rclcpp_components_register_nodes(listener_component "my_components::Listener")
# set(node_plugins "${node_plugins}my_components::Listener;$<TARGET_FILE:listener_component>\n")


# add_library(spawn_component SHARED src/spawn_component.cpp)
# target_compile_definitions(spawn_component PRIVATE "COMPOSITION_BUILDING_DLL")
# ament_target_dependencies(spawn_component
#   "rclcpp"
#   "rclcpp_components"
#   "geometry_msgs"
#   "turtlesim"
#   "std_msgs"
# )

# rclcpp_components_register_nodes(spawn_component "my_components::spawn")
# set(node_plugins "${node_plugins}my_components::spawn;$<TARGET_FILE:spawn_component>\n")

# install(TARGETS
#   moverobot_component
#   listener_component
#   spawn_component
#   ARCHIVE DESTINATION lib
#   LIBRARY DESTINATION lib
#   RUNTIME DESTINATION bin)
  
# install(DIRECTORY
#   launch
#   DESTINATION share/${PROJECT_NAME}
# )
# if(BUILD_TESTING)
#   find_package(ament_lint_auto REQUIRED)
#   # the following line skips the linter which checks for copyrights
#   # uncomment the line when a copyright and license is not present in all source files
#   #set(ament_cmake_copyright_FOUND TRUE)
#   # the following line skips cpplint (only works in a git repo)
#   # uncomment the line when this package is not in a git repo
#   #set(ament_cmake_cpplint_FOUND TRUE)
#   ament_lint_auto_find_test_dependencies()
# endif()

# ament_package()