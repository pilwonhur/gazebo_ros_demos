#include "rrbot_control_example_feedback.h"

using namespace std;

int count1=0;

RRBOT_Feedback::RRBOT_Feedback(int argc,char**argv,int rate=100)
{
	//ros::init(argc,argv,"rrbot_control_example_feedback");	
	if(argc<2)
	{
		std::cout << "Not enough number of arguments!" << std::endl;
	} else if(argc==2)
	{
		if(**(argv+1)=='p')	// note that if char *argv[], then you need to use argv[0]=='p'
		{				// When using char *argv[], then the element of the array argv[] is pointer
						// In other words, it is the array of pointers to char.
						// If char **argv, then even though the meaning is exactly the same, 
						// the usage is different. **argv or, **(argv+1).. actually, **(argv+sizeof(char))
			pub1=nh.advertise<rrbot_control_example::Message1>("/rrbot/joint1_position_controller/command",100);	//<std_msgs::Float64>      
			pub2=nh.advertise<rrbot_control_example::Message1>("/rrbot/joint2_position_controller/command",100);	//<std_msgs::Float64>  
			std::cout << "Position!" << std::endl;
		} else if(**(argv+1)=='t')	// *(argv+1) is the content of the 2nd (char) element. Since that content itself is also an pointer 
		{							//because this pointer is pointing to a string in general. 
		
			std::cout << "Torque!" << std::endl;
			pub1=nh.advertise<rrbot_control_example::Message1>("/rrbot/joint1_torque_controller/command",100);	//<std_msgs::Float64>      
			pub2=nh.advertise<rrbot_control_example::Message1>("/rrbot/joint2_torque_controller/command",100);	//<std_msgs::Float64>      
		}
	}

	sub=nh.subscribe("/gazebo/link_states",1000,this->msgCallback);
	this->rate=rate;
}

// void RRBOT_Feedback::msgCallback(const gazebo_msgs::ModelStates::ConstPtr& msg)
// Note that this callback function will be called almost about 1000hz.
void RRBOT_Feedback::msgCallback(const gazebo_msgs::LinkStates::ConstPtr& msg)
{
	//ROS_INFO("recieved msg: %f",msg->data);
	if(count1%1000==0)
	{
		cout << msg->pose[3].position.x << ",";
		cout << msg->pose[3].position.y << ",";
		cout << msg->pose[3].position.z << endl;
		cout << count1/1000 << endl;
	}
	count1++;
	//cout << "msgCallback" << endl;
}

void RRBOT_Feedback::FeedbackLoop()
{
	ros::Rate loop_rate(rate);
	int i=0;
	while(ros::ok())
	{
		rrbot_control_example::Message1 msg1,msg2;
		msg1.data=sin(i/50.0)*5.0;
		msg2.data=sin(i/50.0)*0.0;
		pub1.publish(msg1);
		pub2.publish(msg2);
		ros::spinOnce();
		loop_rate.sleep();
		i++;
	}	
}

RRBOT_Feedback::~RRBOT_Feedback()
{

}

int main(int argc,char**argv)
{
	ros::init(argc,argv,"rrbot_control_example_feedback");	
	RRBOT_Feedback rrbot(argc,argv,1000);
	rrbot.FeedbackLoop();
	return 0;
}