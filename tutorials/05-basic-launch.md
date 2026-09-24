# Basic Launch
Launch files allow you to configure and run multiple ROS 2 nodes simultaneously using a Python script.

Create a directory named `launch` inside `src/my_package` and save the following file as `src/my_package/launch/launch.py`:

<details>
<summary><b>Basic Listener Node</b></summary>

```pyhon
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
```
</details>

## Updating `CMakeLists.txt`

ROS 2 needs to know what launch scripts a package has after installation. To specify that you want the `launch` directory copied to the final product, you write this:
```cmake
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)
```

## Code breakdown
`generate_launch_description` is the entry point of the launch file. Naming your function something else will not work.
`Node(...)` creates a python object that represents a node you wish to launch.
   - `package` is the name of the package, in this case `my_package`.
   - `executable` is the name of the executable, as specified in the `add_executable` line in the cmake.
`LaunchDescription` is a list of launch actions to do. In this case we are only running a couple of nodes.
> NOTE: The name of the package is both the name of the CMake `project` and the package.xml description

## Running the launch file

Compile the workspace so CMake can install the `launch` directory and ROS 2 can find it.

Once you have compiled and sourced `install/setup.bash`, you can run the launch file using:
```bash
ros2 launch my_package launch.py
```
Which should give you the combined output in 1 terminal window.


