#!/usr/bin/env python

import os
import rospy
from controlvehicle.msg import Maxsonar

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

		for x in range(self.szer):
			print self.tab[x]

	def calc(self,msonar):
		## przedni centralny
		il_kratek = msonar.dwa/10

		self.tab[self.cent_szer+0][self.cent_dl+int(il_kratek)] = self.tab[self.cent_szer+0][self.cent_dl+int(il_kratek)] + 1	
		self.tab[self.cent_szer+1][self.cent_dl+int(il_kratek)] = self.tab[self.cent_szer+1][self.cent_dl+int(il_kratek)] + 1	
		self.tab[self.cent_szer-1][self.cent_dl+int(il_kratek)] = self.tab[self.cent_szer-1][self.cent_dl+int(il_kratek)] + 1	

		## przedni lewy
		il_kratek2 = msonar.trzy/10

		self.tab[self.cent_szer-2][self.cent_dl+int(il_kratek2)] = self.tab[self.cent_szer-2][self.cent_dl+int(il_kratek2)] + 1	
		self.tab[self.cent_szer-3][self.cent_dl+int(il_kratek2)] = self.tab[self.cent_szer-3][self.cent_dl+int(il_kratek2)] + 1	
		self.tab[self.cent_szer-4][self.cent_dl+int(il_kratek2)] = self.tab[self.cent_szer-4][self.cent_dl+int(il_kratek2)] + 1	

		## przedni prawy
		il_kratek3 = msonar.jeden/10

		self.tab[self.cent_szer+2][self.cent_dl+int(il_kratek3)] = self.tab[self.cent_szer+2][self.cent_dl+int(il_kratek3)] + 1	
		self.tab[self.cent_szer+3][self.cent_dl+int(il_kratek3)] = self.tab[self.cent_szer+3][self.cent_dl+int(il_kratek3)] + 1	
		self.tab[self.cent_szer+4][self.cent_dl+int(il_kratek3)] = self.tab[self.cent_szer+4][self.cent_dl+int(il_kratek3)] + 1	

		## tylni
		il_kratek4 = msonar.cztery/10

		self.tab[self.cent_szer+0][self.cent_dl-int(il_kratek4)] = self.tab[self.cent_szer+0][self.cent_dl-int(il_kratek4)] + 1	
		self.tab[self.cent_szer+1][self.cent_dl-int(il_kratek4)] = self.tab[self.cent_szer+1][self.cent_dl-int(il_kratek4)] + 1	
		self.tab[self.cent_szer-1][self.cent_dl-int(il_kratek4)] = self.tab[self.cent_szer-1][self.cent_dl-int(il_kratek4)] + 1	


	def update(self):
		pass
		



class naviClass(object):
	## sranie w banie
	
	
	def __init__(self,map):
		rospy.init_node('naviClass', anonymous=True)
		self.jeden = 0
		self.dwa = 0
		self.trzy = 0
		self.cztery = 0
		self.map = map

	def subscribeSonars(self):
		rospy.Subscriber('maxsonar', Maxsonar, self.coefCallback)
		rospy.spin()		

	def coefCallback(self,msonar):
		self.jeden = msonar.sonar1
		self.dwa = msonar.sonar2 
		self.trzy = msonar.sonar3
		self.cztery = msonar.sonar4
			
		self.map.calc(self)
		self.map.displayMap()

	#	self.printData() ## drukuje wartosci  z sonar√w
		
	
	def printData(self):
		print "{}:{}:{}:{}\n------".format(self.jeden,self.dwa, self.trzy, self.cztery)


if __name__ == '__main__':
	MapObj = mapClass(30,30)	
	NaviObj = naviClass(MapObj)
	NaviObj.subscribeSonars()
	

















