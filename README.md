# joy2q
Interface to bobcat with joystick

This package is a subscriber of joystick topic:/joy
and it forwards the relevant part of the topic to the
LLC topics:
/LLC/EFFORTS/Steering amd /LLC/EFFORTS/Throttle.

In order to use:
1. Clone the repository
2. Enter the repository
3. Compile: catkin build
4. Source devel_test/setup.bash
5. roslaunch joy2q joy2bobcat.launch
