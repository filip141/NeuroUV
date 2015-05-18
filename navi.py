#!/usr/bin/env python

import os
import rospy
from controlvehicle.msg import Maxsonar
from controlvehicle.msg import joy_control_msg as Move

print "start.."


class mapClass(object):
	## mapa przeszkod

	def __init__(self,szer,dl):
		self.szer = szer
		self.dl = dl
		

		self.tab = [0]*szer
		for x in range(len(self.tab)):
			self.tab[x] = [0]*dl
		
		self.cent_szer = self.szer/2
		self.cent_dl = self.dl/2
		self.tab[self.cent_szer][self.cent_dl] = 5
	
	def displayMap(self):
		os.system('clear')		

		for y in reversed(range(self.dl)):
			print self.tab[y]

	def calc(self,msonar):
		try:
			## przedni centralny
			il_kratek = msonar.dwa/10

			self.tab[self.cent_dl+int(il_kratek)][self.cent_szer+0] += 1	
			self.tab[self.cent_dl+int(il_kratek)][self.cent_szer+1] += 1	
			self.tab[self.cent_dl+int(il_kratek)][self.cent_szer-1] += 1	

			## przedni lewy
			il_kratek = msonar.trzy/10
			self.tab[self.cent_dl+int(il_kratek)][self.cent_szer-5] += 1	
			self.tab[self.cent_dl+int(il_kratek)][self.cent_szer-3] += 1	
			self.tab[self.cent_dl+int(il_kratek)][self.cent_szer-4] += 1	

			## przedni prawy
			il_kratek = msonar.jeden/10
			self.tab[self.cent_dl+int(il_kratek)][self.cent_szer+5] += 1	
			self.tab[self.cent_dl+int(il_kratek)][self.cent_szer+3] +=  1	
			self.tab[self.cent_dl+int(il_kratek)][self.cent_szer+4] +=  1	

			## tylni
			il_kratek = msonar.cztery/10
			self.tab[self.cent_dl-int(il_kratek)][self.cent_szer+0] +=  1	
			self.tab[self.cent_dl-int(il_kratek)][self.cent_szer+1] +=  1	
			self.tab[self.cent_dl-int(il_kratek)][self.cent_szer-1] +=  1	

		except IndexError:
			pass

	def refresh(self):
		for x in range(self.szer):
			for y in range(self.dl):
				self.tab[x][y] = 0
		

	def initial_scan(self,msonar):
		
		self.refresh()
		self.calc(msonar)
		self.displayMap()
		
		try:
			ControllerOBJ = Controller()
			ControllerOBJ.turn90deg()
		except rospy.ROSInterruptException:
			pass

		print "okrecilem sie"
			
class Controller(object):
	## steruje robotem

	def __init__(self):
#		rospy.init_node('Controller',anonymous=True)
		self.pub = rospy.Publisher('joyvehicle', Move, queue_size=1)
		self.rate = rospy.Rate(10)
		self.move = Move()
	
	def turn90deg(self):
		self.move.sequence = 2
		self.move.speed = 100
		self.move.powerLR = 0
	
		self.pub.publish(self.move)
		self.rate.sleep()		
		
		#rospy.spin()	
		## close node

class naviClass(object):
	## sranie w banie
	
	
	def __init__(self,map):
		rospy.init_node('naviClass', anonymous=True)
		self.jeden = 0
		self.dwa = 0
		self.trzy = 0
		self.cztery = 0
		self.map = map
		self.move = 1
		self.flag = True
		self.is_started = False 	

	def subscribeSonars(self):
		rospy.Subscriber('maxsonar', Maxsonar, self.coefCallback)
		rospy.Subscriber('joyvehicle', Move, self.moveCallBack)
		rospy.spin()		


	def moveCallBack(self, move):
		self.move = move.sequence

	def coefCallback(self,msonar):
	
		## PIERWSZY SKAN 360 STOPNI
		if not self.is_started:
			self.map.initial_scan(self)
			self.is_started = True		

		"""## ALGORYTM SKANUJACY PO ZATRZYMANIU
		print "1"
		if self.move == 1:
			if self.flag:
				self.map.refresh()
	
			self.jeden = msonar.sonar1
			self.dwa = msonar.sonar2 
			self.trzy = msonar.sonar3
			self.cztery = msonar.sonar4
	
			self.map.calc(self)
			self.map.displayMap()
	
			self.flag = False
		else:
			self.flag = True

	"""
						
		
		
		#self.printData() ## drukuje wartosci  z sonarow
		
	
	def printData(self):
		print "{}:{}:{}:{}\n------".format(self.jeden,self.dwa, self.trzy, self.cztery)
		

if __name__ == '__main__':
	MapObj = mapClass(20,20)	
	NaviObj = naviClass(MapObj)
	NaviObj.subscribeSonars()
	

















