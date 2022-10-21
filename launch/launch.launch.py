import launch
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode


def generate_launch_description():
    """Generate launch description with multiple components."""
    container = ComposableNodeContainer(
        name='my_container',
        namespace='',
        package='rclcpp_components',
        executable='component_container',
        composable_node_descriptions=[
            ComposableNode(
                package='my_components',
                plugin='my_components::spawn',
                name='spawn'),
            # ComposableNode(
            #     package='my_components',
            #     plugin='my_components::Listener',
            #     name='listener'),
            ComposableNode(
                package='my_components',
                plugin='my_components::publisherNode',
                name='publisher'),
            # ComposableNode(
            #     package='my_components',
            #     plugin='my_components::clear',
            #     name='clear'),
            ComposableNode(
                package='my_components',
                plugin='my_components::reset',
                name='reset'),
        ],
        output='screen',
    )

    return launch.LaunchDescription([container])