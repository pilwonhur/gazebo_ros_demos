#include <ros/ros.h>
#include "rrbot_control_example/Message1.h"
#include "gazebo_msgs/LinkStates.h"
#include <iostream>
#include <math.h>

class RRBOT_Feedback{
private:
	ros::NodeHandle nh;
	ros::Publisher pub1, pub2;
	ros::Subscriber sub;
	int rate=0;


public:
	RRBOT_Feedback(int,char**,int);
	~RRBOT_Feedback();
	static void msgCallback(const gazebo_msgs::LinkStates::ConstPtr& msg);
	void FeedbackLoop();


};