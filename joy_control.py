#!/usr/bin/env python
import rospy
from controlvehicle.msg import joy_control_msg
from sensor_msgs.msg import Joy

#Class to control vehicle via joystick device using ros joy drivers
class rosVehicleControl(object):
    rosPublisher = None
    joyControlMsg = None
    speedaxis_ = 1
    powerLRaxis_ = 0

    #Constructor function initialize publisher and initialize node
    def __init__(self):
        self.rosPublisher = rospy.Publisher("joyvehicle", joy_control_msg, queue_size=1)
	rospy.init_node("controlvehicle_joy", anonymous = True)
	self.joyControlMsg = joy_control_msg()

    #Subscribe Messages 
    def subscribeMsgs(self):
	rospy.Subscriber("joy", Joy, self.joyHandle)
	#Prevent to exit from script
	rospy.spin()

    #Handle joystick event
    def joyHandle(self,data):
	scaledSpeed = 100*data.axes[self.speedaxis_]
	scaledPowerLR = -100*data.axes[self.powerLRaxis_]
	self.joyControlMsg.speed = int(scaledSpeed)
	self.joyControlMsg.powerLR = int(scaledPowerLR)
	print "Scaled Values : " + str(scaledSpeed) + "                  " + str(scaledPowerLR)
	if scaledSpeed <20 and scaledSpeed > -20 and scaledPowerLR < 20 and scaledPowerLR > -20:
	     self.joyControlMsg.sequence = 1
	elif scaledSpeed <20  and  scaledSpeed >-20 and scaledPowerLR > 20:
	     self.joyControlMsg.sequence = 3
	elif scaledSpeed <20  and scaledSpeed > -20 and scaledPowerLR < -20:
	     self.joyControlMsg.sequence = 3
	elif scaledSpeed >20  and scaledPowerLR > -20 and scaledPowerLR < 20:
	     self.joyControlMsg.sequence = 2
	elif scaledSpeed <-20  and scaledPowerLR > -20 and scaledPowerLR < 20:
	     self.joyControlMsg.sequence = 2                                                                      
	elif scaledSpeed >20  and scaledPowerLR < -20:                                                                                	
             self.joyControlMsg.sequence = 4
	elif scaledSpeed >20  and scaledPowerLR > 20: 
     	     self.joyControlMsg.sequence = 4
	elif scaledSpeed <-20  and scaledPowerLR > 20: 
     	     self.joyControlMsg.sequence = 4
	else:
     	     self.joyControlMsg.sequence = 4

	self.rosPublisher.publish(self.joyControlMsg)

if __name__ == '__main__':
    try:
        rs = rosVehicleControl()
	rs.subscribeMsgs()
    except rospy.ROSInterruptException:
        pass
