# CMake generated Testfile for 
# Source directory: /home/pi/catkin_ws/src/robot_upstart
# Build directory: /home/pi/catkin_ws/build/robot_upstart
# 
# This file includes the relevent testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(_ctest_robot_upstart_roslint_package "/home/pi/catkin_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/indigo/share/catkin/cmake/test/run_tests.py" "/home/pi/catkin_ws/build/test_results/robot_upstart/roslint-robot_upstart.xml" "--working-dir" "/home/pi/catkin_ws/build/robot_upstart" "--return-code" "/home/pi/catkin_ws/src/roslint/scripts/test_wrapper /home/pi/catkin_ws/build/test_results/robot_upstart/roslint-robot_upstart.xml make roslint_robot_upstart")
ADD_TEST(_ctest_robot_upstart_nosetests_test "/home/pi/catkin_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/indigo/share/catkin/cmake/test/run_tests.py" "/home/pi/catkin_ws/build/test_results/robot_upstart/nosetests-test.xml" "--return-code" "/usr/bin/cmake -E make_directory /home/pi/catkin_ws/build/test_results/robot_upstart" "/usr/bin/nosetests-2.7 -P --process-timeout=60 --where=/home/pi/catkin_ws/src/robot_upstart/test --with-xunit --xunit-file=/home/pi/catkin_ws/build/test_results/robot_upstart/nosetests-test.xml")
