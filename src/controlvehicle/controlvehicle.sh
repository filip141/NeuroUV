#! /bin/bash
# /etc/init.d/controlvehicle
#!/bin/sh
### BEGIN INIT INFO
# Provides: controlvehicle
# Required-Start: $remote_fs $syslog
# Required-Stop: $remote_fs $syslog
# Default-Start: 2 3 4 5
# Default-Stop: 0 1 6
# Short-Description: Start ROS on boot
# Description: Start Ros system for robot control over network
### END INIT INFO
source /opt/ros/indigo/setup.bash
source /home/pi/catkin_ws/devel/setup.bash
export LC_ALL="C"
export ROS_MASTER_URI="http://raspberrypi:11311/"
export ROS_PACKAGE_PATH=/home/pi/catkin_ws/src/controlvehicle:$ROS_PACKAGE_PATH
export ROS_IP=192.168.1.102
# initialze the pidfile
CAROBOT_PIDFILE='/var/run/controlvehicle.pid'
ROS_USER=pi
touch $CAROBOT_PIDFILE
/bin/chown $ROS_USER\:$ROS_USER $CAROBOT_PIDFILE
# roslaunch vars
ROSLAUNCH_BIN="/opt/ros/indigo/bin/roslaunch"
ROSLAUNCH_ARGS="--pid=$CAROBOT_PIDFILE"
# set path to launchfile
ROSLAUNCH_FILE="/home/pi/catkin_ws/src/controlvehicle/launch/controlvehicle.launch"
# carry out specific functions when asked by the system
case "$1" in
  start)
    echo "Starting controlvehicle service ..."
    su -c "$ROSLAUNCH_BIN $ROSLAUNCH_ARGS $ROSLAUNCH_FILE" $ROS_USER &
    ;;  
  stop)
    kill -2 $(cat $CAROBOT_PIDFILE) > /dev/null
    echo -n "" > $CAROBOT_PIDFILE
    echo "Stopping controlvehicle services ..."
    ;;  
  restart)
    $0 stop
    sleep 3
    $0 start
    ;;  
  *)  
    echo "Usage: $0 {start|stop|restart}"
    exit 1
    ;;  
esac
exit 0
