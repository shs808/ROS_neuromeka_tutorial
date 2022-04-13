
#include <string>
#include <stdio.h>
#include <ros/ros.h>
#include <indy_driver/GripperSg.h>
#include <indy_driver/ChangeSet.h>
#include <indy_driver/Gohome.h>
double gripp = 0;
void msgcallback(const indy_driver::GripperSg::ConstPtr& msg){
	gripp=msg->grip ;

}

int main(int argc, char **argv)
{   
    
    ros::init(argc, argv, "gazebo_grip");
    ros::NodeHandle n5,n6,n2;
    ros::AsyncSpinner spinner(1);
    spinner.start();
    
    // Place code here.
	ros::Subscriber sub = n5.subscribe<indy_driver::GripperSg>("Gripper", 10, msgcallback);
	ros::Publisher pub = n5.advertise<indy_driver::GripperSg>("Gripper", 10);
	ros::Publisher pub1 = n6.advertise<indy_driver::ChangeSet>("Change", 10);
    ros::Publisher pub2 = n2.advertise<indy_driver::Gohome>("Hometrg", 10);
	indy_driver::GripperSg msg;
	indy_driver::ChangeSet msg1;
	indy_driver::Gohome msg2;
    ros::Rate loop_rate(5);
    while (ros::ok()){

			if(gripp==1){
				//data.
				//indySocket.sendCommand(402, data,len);
                ROS_INFO_NAMED("gazebo_grip", "**********Gazebo grip ON*********");
				msg.grip=0;
				msg1.change = 1;
				pub.publish(msg);
				pub1.publish(msg1);
			}
			else if(gripp==2){
                ROS_INFO_NAMED("gazebo_grip", "*********Gazebo grip OFF*********");
				msg.grip=0;
				msg2.gohome=0;
                pub.publish(msg);
				pub2.publish(msg2);
			}
        loop_rate.sleep();
        //ros::spin();
    }
    ros::shutdown();
    return 0;
}