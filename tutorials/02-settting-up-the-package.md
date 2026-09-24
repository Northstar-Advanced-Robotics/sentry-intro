# Setting up the package

Before running any commands, make sure to enter the container environment.

## Entering container shell

`repo.py` is a script we provide for common repository operations such as entering a shell inside the container, building the image, and compiling code.

Entering a shell is as simple as `python repo.py shell`

## Creating a ROS 2 package skeleton 

`cd` into `src`, then you can create the package using:
```bash
ros2 pkg create --build-type ament_cmake --license MIT my_package
```
You should have a directory named `my_package` under `src`. If you accidentally make it somewhere else, you can simply delete it.

This command will create a `package.xml` and a `CMakeLists.txt`, which if you remember from lesson 1, are the only required files.

## Stating dependencies

### Declaring dependencies in `package.xml`
Every ROS 2 C++ node needs `rclcpp`, the ros c++ client lib.
To properly add this library as a dependency, we need to add some lines to `package.xml`.

There are many types of dependencies, such as `build_depend` and `exec_depend`, however to state that a dependency is required for both compiling and running code, we use `<depend>mypkg</depend>` 

> NOTE: Adding dependencies to `package.xml` operates on the scope of ros2 packages. Regular C++ libraries should not be added to the `package.xml`

The purpose of stating dependencies in `package.xml` is not to make it available to code, but to make `colcon`, the ros2 build system, effectively coordinate building the ros2 workspace.

<details>
<summary><b>Finished `package.xml`</b></summary>

```xml
<?xml version="1.0"?>
<?xml-model href="http://download.ros.org/schema/package_format3.xsd" schematypens="http://www.w3.org/2001/XMLSchema"?>
<package format="3">
  <name>my_package</name>
  <version>0.0.0</version>
  <description>TODO: Package description</description>
  <maintainer email="root@todo.todo">root</maintainer>
  <license>TODO: License declaration</license>

  <buildtool_depend>ament_cmake</buildtool_depend>

  <depend>rclcpp</depend> <!-- ADDED -->
  <depend>std_msgs</depend> <!-- ADDED -->

  <test_depend>ament_lint_auto</test_depend>
  <test_depend>ament_lint_common</test_depend>

  <export>
    <build_type>ament_cmake</build_type>
  </export>
</package>
```
</details>

### Stating dependencies in `CMakeLists.txt`

Declaring dependencies in `CMakeLists.txt` makes them available in code.
You can declare them using `find_package(<package> REQUIRED)`

<details>
<summary><b>`CMakeLists.txt` with dependencies</b></summary>

```cmake
cmake_minimum_required(VERSION 3.8)
project(my_package)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Always needed, provides cmake integration with colcon
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED) # <== ADDED
find_package(std_msgs REQUIRED) # <== ADDED

# ...
ament_package()
```
</details>

## Writing the build script

Just declaring dependencies in `CMakeLists.txt` won't get us very far though.
The main goal of this file is to describe what executables/libraries are being built and how.

To build an executable, one needs to declare the target with its sources like so:
```cmake
add_executable(my_publisher_node src/publisher.cpp)
```
> NOTE: Header files (`.h` and `.hpp`) are not included in add_executable source list.

To declare this target needs `rclcpp`, you write the following:
```cmake
target_link_libraries(my_publisher_node PRIVATE
  rclcpp::rclcpp
  std_msgs::std_msgs
)
```
> NOTE: In official ROS 2 docs, you might see `ament_target_dependencies` rather than `target_link_libraries`.
We use `target_link_libraries` because it works not just for ros2 packages, but for standard C++ libraries as well. 

This command specifies both linking and adding the necessary include paths.

We will also specify C++ 20 so we can use the modern goodies.
```cmake
target_compile_features(my_publisher_node PRIVATE cxx_std_20)
```

This is enough to compile the executable correctly, but we need to add one last thing to properly integrate it into the ROS 2 ecosystem:
```cmake
install(TARGETS
  my_publisher_node
  DESTINATION lib/${PROJECT_NAME}
)
```

This tells cmake to copy the executable to `<install-prefix>/lib/mypub/my_publisher_node` during installation.
This is where ROS 2 expects package executables to be located. Without this line ROS 2 cannot run the executable because it does not know where it is. 
> WARNING: `ament_package()` must be the last line of `CMakeLists.txt`.

## Final check

If you try to build right now, you will get an error because `src/mypub/src/publisher.cpp` does not exist. So we will write a hello world at that location so that cmake can run and generate the neccessary information for IDE's to provide autocomplete
<details>
<summary><b>Hello World</b></summary>

```c++
#include <iostream>

int main() {
  std::cout << "Hello World\n";
}
```
</details>

Once you have the hello world writen, you should be able to compile with no errors using `./repo.py compile`.
