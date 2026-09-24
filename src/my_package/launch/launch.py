from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    publisher_node = Node(
        package='my_package',
        executable='my_publisher_node',
    )

    listener_node = Node(
        package='my_package',
        executable='my_listener_node',
    )

    return LaunchDescription([publisher_node, listener_node])
