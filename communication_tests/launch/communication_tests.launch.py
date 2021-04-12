from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument(
            's',
            default_value='0'
        ),
        DeclareLaunchArgument(
            'r',
            default_value='1000'
        ),
        DeclareLaunchArgument(
            'f',
            default_value='1000'
        ),
        DeclareLaunchArgument(
            'p',
            default_value=''
        ),
        DeclareLaunchArgument(
            'd',
            default_value='1'
        ),
        DeclareLaunchArgument(
            'l',
            default_value='0'
        ),
        DeclareLaunchArgument(
            'pt',
            default_value='bypass',
            description='Topic the publisher publishes to bypass node'
        ),
        DeclareLaunchArgument(
            'st',
            default_value='communication_test',
            description='Topic the subscriber subscribe from bypass node'
        ),
        Node(
            name='ct_subscriber',
            package='communication_tests',
            executable='communication_tests_subscriber',
            arguments=['-s', LaunchConfiguration('s'), '-r', LaunchConfiguration('r'), '-f', LaunchConfiguration('f'), '-p', LaunchConfiguration('p'), '-d', LaunchConfiguration('d'), '-l', LaunchConfiguration('l'), '-t', LaunchConfiguration('st')]
        ),
        Node(
            name='ct_publisher',
            package='communication_tests',
            executable='communication_tests_publisher',
            arguments=['-s', LaunchConfiguration('s'), '-r', LaunchConfiguration('r'), '-f', LaunchConfiguration('f'), '-p', LaunchConfiguration('p'), '-d', LaunchConfiguration('d'), '-l', LaunchConfiguration('l'), '-t', LaunchConfiguration('pt')]
        )
    ])
