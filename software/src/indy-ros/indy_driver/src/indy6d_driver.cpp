#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <indy_driver/GripperSg.h>
#include <indy_driver/ChangeSet.h>
#include "SocketHandler/IndyDCPSocket.h"
#include "TrajectoryDownloader/JointTrajectoryDownloader.h"
#include <indy_driver/Gohome.h>

#define JOINT_DOF 6
#define DEGREE M_PI/180
double gripp=0;
void GripperClose(void);
void GripperOpen(void);
void msgcallback(const indy_driver::GripperSg::ConstPtr& msg){
	gripp=msg->grip ;

}
int main(int argc, char ** argv)
{
	ros::init(argc, argv, "indy6d_driver");
	ros::NodeHandle n;
	ros::NodeHandle n5,n6,n2;
	ros::AsyncSpinner spinner(1);
    spinner.start();
	std::string robotName, ip;
	int port;
	double q[JOINT_DOF];
	sensor_msgs::JointState joint_state;
    //indy_driver::IndyMsg msg;
	// override IP/port with ROS params, if available
	ros::param::param<std::string>("robot_name", robotName, "");
	ros::param::param<std::string>("robot_ip_address", ip, SERVER_IP);
	ros::param::param<int>("~port", port, SERVER_PORT);

	// check for valid parameter values
	if (robotName.empty())
	{
		ROS_ERROR("No valid robot's name found.  Please set ROS 'robot_name' param");
		return false;
	}
	if (ip.empty())
	{
		ROS_ERROR("No valid robot IP address found.  Please set ROS 'robot_ip_address' param");
		return false;
	}
	if (port <= 0)
	{
		ROS_ERROR("No valid robot IP port found.  Please set ROS '~port' param");
		return false;
	}

	IndyDCPSocket indySocket;
	indySocket.init(robotName, ip, port);
	ros::Rate loop_rate(10);
	ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 10);
	ros::Subscriber sub = n5.subscribe<indy_driver::GripperSg>("Gripper", 10, msgcallback);
	ros::Publisher pub = n5.advertise<indy_driver::GripperSg>("Gripper", 10);
	ros::Publisher pub1 = n6.advertise<indy_driver::ChangeSet>("Change", 10);
	ros::Publisher pub2 = n2.advertise<indy_driver::Gohome>("Hometrg", 10);
	indy_driver::GripperSg msg;
	indy_driver::ChangeSet msg1;
	indy_driver::Gohome msg2;
	JointTrajectoryDownloader jmotionInterface(indySocket, JOINT_DOF);
	jmotionInterface.init();
	int idx;
	char val;
	//gripp = 1;

	while (ros::ok())
	{
		if (indySocket.isWorking())
		{
			Data data, gripdata, sendata;
			unsigned int len;
			if(gripp==1){
				idx = 8;
				val = 0;
				memcpy(gripdata.byte, &idx, sizeof(int));
				memcpy(gripdata.byte+sizeof(int), &val, sizeof(char));
				indySocket.sendCommand(402,gripdata,5);
				indySocket.getFeedback(402, gripdata, len);
				idx = 9;
				val = 1;
				memcpy(gripdata.byte, &idx, sizeof(int));
				memcpy(gripdata.byte+sizeof(int), &val, sizeof(char));
				indySocket.sendCommand(402,gripdata,5);
				indySocket.getFeedback(402, gripdata, len);

				ROS_INFO_NAMED("gazebo_grip", "**********Grip ON*********");
				//for(int i=0;i<4;i++) printf("double 6dArr = %d,%d,%d,%d,%d,%d,%d,%d",gripdata.intArr[i*8],gripdata.intArr[i*8+1],gripdata.intArr[i*8+2],gripdata.intArr[i*8+3],gripdata.intArr[i*8+4],gripdata.intArr[i*8+5],gripdata.intArr[i*8+6],gripdata.intArr[i*8+7]);
				//for(int i = 0; i<10;i++)
				/*printf("%d, %d, %d, %d, %d \n",gripdata.intArr[0],gripdata.intArr[1],gripdata.intArr[2],gripdata.intArr[3],gripdata.intArr[4]);
				printf("%d, %d, %d, %d, %d \n",gripdata.int6dArr[0],gripdata.int6dArr[1],gripdata.int6dArr[2],gripdata.int6dArr[3],gripdata.int6dArr[4]);
				printf("%d, %d, %d, %d, %d \n",gripdata.int7dArr[0],gripdata.int7dArr[1],gripdata.int7dArr[2],gripdata.int7dArr[3],gripdata.int7dArr[4]);
				printf("%d \n",gripdata.intVal);*/
				//printf("%d, %d, %d, %d, %d \n",gripdata.intArr[5],gripdata.intArr[6],gripdata.intArr[7],gripdata.intArr[8],gripdata.intArr[9]);
				//printf("%d, %d, %d, %d, %d \n",gripdata.intArr[10],gripdata.intArr[11],gripdata.intArr[12],gripdata.intArr[13],gripdata.intArr[14]);
				//printf("%d, %d, %d, %d, %d \n",gripdata.intArr[15],gripdata.intArr[16],gripdata.intArr[17],gripdata.intArr[18],gripdata.intArr[19]);
				//printf("%d, %d, %d, %d, %d \n",gripdata.intArr[20],gripdata.intArr[21],gripdata.intArr[22],gripdata.intArr[23],gripdata.intArr[24]);

				msg.grip=0;
				msg1.change = 1;
				pub.publish(msg);
				pub1.publish(msg1);
			}
			else if(gripp==2){
				idx = 9;
				val = 0;
				memcpy(gripdata.byte, &idx, sizeof(int));
				memcpy(gripdata.byte+sizeof(int), &val, sizeof(char));
				indySocket.sendCommand(402,gripdata,5);
				indySocket.getFeedback(402, gripdata, len);
				idx = 8;
				val = 1;
				memcpy(gripdata.byte, &idx, sizeof(int));
				memcpy(gripdata.byte+sizeof(int), &val, sizeof(char));
				indySocket.sendCommand(402,gripdata,5);
				indySocket.getFeedback(402, gripdata, len);
				ROS_INFO_NAMED("gazebo_grip", "**********Grip OFF*********");
				msg.grip=0;
				msg2.gohome = 0;
				pub.publish(msg);
				pub2.publish(msg2);
			}
			indySocket.sendCommand(320, data, 0);
			indySocket.getFeedback(320, data, len);
			//printf("q: ");
			for (int i = 0; i < JOINT_DOF; i++)
			{
				q[i] = data.double6dArr[i];
				//printf("%f, ", q[i]);
			}
			//printf("\n");
		}
		
		joint_state.header.stamp = ros::Time::now();
		joint_state.name.resize(JOINT_DOF);
		joint_state.position.resize(JOINT_DOF);

		joint_state.name[0] = "joint0";
		joint_state.position[0] = q[0] * DEGREE;
		joint_state.name[1] = "joint1";
		joint_state.position[1] = q[1] * DEGREE;
		joint_state.name[2] = "joint2";
		joint_state.position[2] = q[2] * DEGREE;
		joint_state.name[3] = "joint3";
		joint_state.position[3] = q[3] * DEGREE;
		joint_state.name[4] = "joint4";
		joint_state.position[4] = q[4] * DEGREE;
		joint_state.name[5] = "joint5";
		joint_state.position[5] = q[5] * DEGREE;
		joint_pub.publish(joint_state);
		//pub.publish(msg);
		//ros::spinOnce();
		loop_rate.sleep();
	}

	indySocket.stop();

	return 0;
}


