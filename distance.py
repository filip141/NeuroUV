#!/usr/bin/env python
import rospy
import time
from controlvehicle.msg import ardu_imu
from geometry_msgs.msg import Vector3

## Function to count distance from strart point 
class distanceMeter(object):

    ##Object initialization
    def __init__(self):
	self.angle = []
	self.acc = [] 
	self.distSum = 0
	self.index = 0
        rospy.init_node('distanceMeter', anonymous=True)

    ##init subscribers
    def subscribeDistance(self):
        rospy.Subscriber("mgeuler", Vector3, self.angleCallback)
        rospy.Subscriber("imu", ardu_imu, self.accCallback)

	rospy.spin()
    #Accelerometer Callback
    def accCallback(self, aimu):
	self.acc.append(aimu.accValues.y)
	
	
    #Angles Callback
    def angleCallback(self, euler):
	if self.index == 5:
	    self.calculateDist()
	    self.angle = []
	    self.index = 0
	self.angle.append(euler.x)
	self.index = self.index + 1 
        
    #Calculate resultant Acceleration
    def calculateDist(self):
        self.angle.sort()
	print self.angle[5]
	

if __name__ == '__main__':

    distObj = distanceMeter()
    distObj.subscribeDistance() 

    

