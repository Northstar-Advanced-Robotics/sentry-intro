# Writing a ROS 2 node

Before writing any code, make sure to enter the container environment, otherwise your IDE will go crazy.

## Entering container shell

`repo.py` is a script we provide for common repository operations such as entering a shell inside the container, building the image, and compiling code.

Entering a shell is as simple as `python repo.py shell`

## Creating a ROS 2 Node skeleton 

`cd` into `src`, then you can create the node using:
```bash
ros2 pkg create --build-type --license MIT ament_cmake mypub
```

This command will create a `package.xml` and a `CMakeLists.txt`, which if you remember from lesson 1, are the only required files.

## Stating dependencies

Every ROS 2 C++ node needs `rclcpp`, the ros c++ client lib.
To properly add this library as a dependency, we need to add some lines to `package.xml`.

There are many types of dependencies, such as `buildtool_depend` and `exec_depend`, however to state that a dependency is required for both compiling and running code, we use `<depend>mypkg..<\depend>` 

> NOTE: Adding dependencies to `package.xml` operates on the scope of ros2 packages. Regular C++ libraries should not be added to the `package.xml`

The purpose of stating dependencies in `package.xml` is not to make it available to code, but to make `colcon`, the ros2 build system, effectively coordinate building the ros2 workspace.

<details>
<summary><b>`package.xml`</b></summary>

```xml
<?xml version="1.0"?>
<?xml-model href="http://download.ros.org/schema/package_format3.xsd" schematypens="http://www.w3.org/2001/XMLSchema"?>
<package format="3">
  <name>mypub</name>
  <version>0.0.0</version>
  <description>TODO: Package description</description>
  <maintainer email="root@todo.todo">root</maintainer>
  <license>TODO: License declaration</license>

  <buildtool_depend>ament_cmake</buildtool_depend>

  <depend>rclcpp</depend> <-- ADDED

  <test_depend>ament_lint_auto</test_depend>
  <test_depend>ament_lint_common</test_depend>

  <export>
    <build_type>ament_cmake</build_type>
  </export>
</package>
```
</details>
