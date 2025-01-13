#!usr/bin/env python
import rospy
import math
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist
from std_msgs.msg import Float32, Double[]

THRESHOLD = 1.0
LOW_BOUND = 0.5
UP_BOUND = 10.5

pose1 = Pose()
pose2 = Pose()

obs1 = Double[]
obs2 = Double[]

def Wall_Hitted (pose):
	return pose.x < LOW_BOUND or pose.y < LOW_BOUND or pose.x > UP_BOUND or pose.y > UP_BOUND


def callback_position (pose, turtle):
	global pose1
	global pose2
	
	if turtle == 'turtle1':
		pose1 = pose
	elif turtle == 'turtle2':
		pose2 = pose


def Distance(x, y):
	return math.sqrt((x)**2+(y)**2)


def callback_obs (obstacles, turtle):
	global obs1
	global obs2
	if turtle == 'turtle1':
		obs1 = obstacles
	elif turtle == 'turtle2':
		obs2 = obstacles
	

def check():
	rospy.init_node("Distance_node", anonymous = True)
	global pose1
	global pose2
	stop = Twist()
	distance = Float32()
	flag1 = False
	flag2 = False
	
	dist = rospy.Publisher('distance', Float32, queue_size= 10)
	rospy.Subscriber('turtle1/pose', Pose, callback_position, callback_args= 'turtle1')
	rospy.Subscriber('turtle2/pose', Pose, callback_position, callback_args= 'turtle2')
	
	rospy.Subscriber('turtle1/obstacles', Double[], callback_obs, callback_args= 'turtle1')
	rospy.Subscriber('turtle2/obstacles', Double[], callback_obs, callback_args= 'turtle1')
	
	vel1 = rospy.Publisher('turtle1/cmd_vel', Twist, queue_size= 10)
	vel2 = rospy.Publisher('turtle2/cmd_vel', Twist, queue_size= 10)
	
	rate = rospy.Rate(10)
	rate.sleep()
	while not rospy.is_shutdown():
		x_distance = pose1.x - pose2.x
		y_distance = pose1.y - pose2.y
		distance = Distance(x_distance, y_distance)
		dist.publish(distance)
		
		if distance < THRESHOLD:
			stop.linear.x = 0.0
			stop.linear.y = 0.0
			stop.angular.z = 0.0
			vel1.publish(stop)
			vel2.publish(stop)
			print("The turtles are too close: GAME OVER")
			print("Restart the tabs")
			rospy.signal_shutdown("GAME OVER")
		
		if Wall_Hitted(pose1) or flag1:
			vel1.publish(stop)
			if flag1 == False:
				print("Turtle 1 hitted the wall: Player 1 GAME OVER")
				flag1 = True
		elif Wall_Hitted(pose2) or flag2:
			vel2.publish(stop)
			if flag2 == False:
				print("Turtle 2 hitted the wall: Player 2 GAME OVER")
				flag2 = True
				
		for i in range(len(obs1)):
			if obs1(i) < THRESHOLD:
				stop.linear.x = 0.0
				stop.linear.y = 0.0
				stop.angular.z = 0.0
				vel1.publish(stop)
				print("Turtle 1 hitted an obstacle: Player 1 GAME OVER")
				flag1 = True
				
		for i in range(len(obs2)):
			if obs2(i) < THRESHOLD:
				stop.linear.x = 0.0
				stop.linear.y = 0.0
				stop.angular.z = 0.0
				vel2.publish(stop)
				print("Turtle 2 hitted an obstacle: Player 2 GAME OVER")
				flag2 = True
			
		if flag1 == True and flag2 == True:
			print("Both player GAME OVER")
			print("Restart the tabs")
			rospy.signal_shutdown("GAME OVER")
		
		rate.sleep()


if __name__ == '__main__':
	check()
