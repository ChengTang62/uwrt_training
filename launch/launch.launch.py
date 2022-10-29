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
            # ComposableNode(
            #     package='uwrt_training',
            #     plugin='uwrt_training::spawn',
            #     name='spawn'),
            # ComposableNode(
            #     package='uwrt_training',
            #     plugin='uwrt_training::Listener',
            #     name='listener'),
            # ComposableNode(
            #     package='uwrt_training',
            #     plugin='uwrt_training::publisherNode',
            #     name='publisher'),
            # ComposableNode(
            #     package='uwrt_training',
            #     plugin='uwrt_training::clear',
            #     name='clear'),
            ComposableNode(
                package='uwrt_training',
                plugin='uwrt_training::reset',
                name='reset'),
            # ComposableNode(
            #     package='uwrt_training',
            #     plugin='uwrt_training::distance',
            #     name='distance'),
            # ComposableNode(
            #     package='uwrt_training',
            #     plugin='uwrt_training::Move',
            #     name='move'),
        ],
        output='screen',
    )

    return launch.LaunchDescription([container])
