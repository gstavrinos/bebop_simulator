#!/usr/bin/env python
import rospy
from hector_uav_msgs.msg import LandingActionGoal
from hector_uav_msgs.msg import TakeoffActionGoal
from std_msgs.msg import Empty

landing_pub = None
takeoff_pub = None
emergency_pub = None

def init():
    global landing_pub, takeoff_pub, emergency_pub
    rospy.init_node('hector_to_bebop')
    landing_pub = rospy.Publisher("action/landing/goal", LandingActionGoal, queue_size=1);
    takeoff_pub = rospy.Publisher("action/takeoff/goal", TakeoffActionGoal, queue_size=1);
    emergency_pub = rospy.Publisher("action/emergency/goal", LandingActionGoal, queue_size=1);
    rospy.Subscriber("bebop/land", Empty, landing_callback)
    rospy.Subscriber("bebop/takeoff", Empty, takeoff_callback)
    rospy.Subscriber("bebop/reset", Empty, emergency_callback)
    while not rospy.is_shutdown():
        rospy.spin()

def landing_callback(msg):
    global landing_pub
    msg_ = LandingActionGoal()
    landing_pub.publish(msg_)

def takeoff_callback(msg):
    global takeoff_pub
    msg_ = TakeoffActionGoal()
    takeoff_pub.publish(msg_)

def emergency_callback(msg):
    global emergency_pub
    msg_ = LandingActionGoal()
    emergency_pub.publish(msg_)

if __name__ == '__main__':
    init()