# two_drones_pkg

Completed ROS Noetic package for MIT VNAV 2023 Lab 2.

Build from the root of a catkin workspace:

```bash
catkin build two_drones_pkg
source devel/setup.bash
```

Run the moving scenario:

```bash
roslaunch two_drones_pkg two_drones.launch
```

Run the static scenario:

```bash
roslaunch two_drones_pkg two_drones.launch static:=True
```

Student: Wenqian Zhang (24020036087)
