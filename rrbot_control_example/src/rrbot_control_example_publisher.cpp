#include <ros/ros.h>
#include "rrbot_control_example/Message1.h"
#include <math.h>

int main(int argc,char**argv)
{
	ros::init(argc,argv,"rrbot_control_example_publisher");
	ros::NodeHandle nh;
	ros::Publisher pub1, pub2;

	if(argc<2)
	{
		std::cout << "Not enough number of arguments!" << std::endl;
		return 0;
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

	ros::Rate loop_rate(50);
	int i=0;
	while(ros::ok())
	{
		rrbot_control_example::Message1 msg1,msg2;
		msg1.data=sin(i/50.0)*2.0;
		msg2.data=sin(i/50.0)*0.0;
		pub1.publish(msg1);
		pub2.publish(msg2);
		ros::spinOnce();
		loop_rate.sleep();
		i++;
	}
	return 0;
}