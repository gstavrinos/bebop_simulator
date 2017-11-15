#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist

def init():
    rospy.init_node('bebop_hover')
    twist_pub = rospy.Publisher("bebop_hover/cmd_vel", Twist, queue_size=1);
    while not rospy.is_shutdown():
        twist_pub.publish(Twist())
        rospy.sleep(0.4)

if __name__ == '__main__':
    init()