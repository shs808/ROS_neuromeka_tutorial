#include <string>
#include <ros/ros.h>
#include <indy_driver/IndyMsg.h>
#include <indy_driver/ObjectSet.h>
#include <indy_driver/TargetSet.h>
#include <indy_driver/moveon.h>
#include <indy_driver/ChangeSet.h>
#include <indy_driver/Converseon.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <tf/tf.h>

#define JOINT_DOF 6
#define DEGREE M_PI/180
using namespace std;

double ob[6]={0.4,0.5,0.9,0,181,91};
double tr[6]={0.4,0.5,0.9,0,181,91};
double chg= 0;
double cvg= 0;

void msgcallback(const indy_driver::ObjectSet::ConstPtr& obmsg){
	ob[0]=obmsg->ox ;
	ob[1]=obmsg->oy ;
	ob[2]=obmsg->oz ;
	ob[3]=obmsg->oR ;
	ob[4]=obmsg->oP ;
	ob[5]=obmsg->oY ;
}
void msgcallback1(const indy_driver::TargetSet::ConstPtr& trmsg1){
    tr[0] = trmsg1->tx;
    tr[1] = trmsg1->ty;
    tr[2] = trmsg1->tz;
    tr[3] = trmsg1->tR;
    tr[4] = trmsg1->tP;
    tr[5] = trmsg1->tY;
}

void msgcallback2(const indy_driver::Converseon::ConstPtr& msg2){
	cvg=msg2->converge ;
}

void msgcallback3(const indy_driver::ChangeSet::ConstPtr& msg3){
	chg=msg3->change ;
}

int main(int argc, char ** argv)
{
    ifstream fread;
	ros::init(argc, argv, "EulerToQuat");
	ros::NodeHandle n2,n3,n4,n6,n7,n8;
	ros::AsyncSpinner spinner(8);
    spinner.start();
	ros::Publisher pub = n8.advertise<indy_driver::IndyMsg>("Move_coordinate", 10);
	ros::Publisher pub1 = n4.advertise<indy_driver::moveon>("Go_to_pose", 10);
	ros::Publisher pub2 = n7.advertise<indy_driver::Converseon>("Converseon", 10);
	ros::Publisher pub3 = n6.advertise<indy_driver::ChangeSet>("Change", 10);
	ros::Subscriber sub = n2.subscribe<indy_driver::ObjectSet>("ObjectSet", 10, msgcallback);
	ros::Subscriber sub1 = n3.subscribe<indy_driver::TargetSet>("TargetSet", 10, msgcallback1);
	ros::Subscriber sub2 = n7.subscribe<indy_driver::Converseon>("Converseon", 10, msgcallback2);
	ros::Subscriber sub3 = n6.subscribe<indy_driver::ChangeSet>("Change", 10, msgcallback3);
	indy_driver::IndyMsg msg;
	indy_driver::moveon msg1;
	indy_driver::Converseon msg2;
	indy_driver::ChangeSet msg3;
	ros::Rate loop_rate(10);
	tf::Quaternion q;
	//ros::AsyncSpinner spinner(2);
    //spinner.start();
    //double d[7];
	while (ros::ok())
	{
		// fread.open("/home/hwj/catkin_ws/src/indy-ros/indy_driver/src/txtdata.txt");
		// fread >> d[0];
		// fread >> d[1];
		// fread >> d[2];
		// fread >> d[3];
		// fread >> d[4];
		// fread >> d[5];
		// fread >> d[6];
		// fread.close();
	    if(cvg==1){
		ROS_INFO_NAMED("Object_in", "Converse Object_coordinate : X = %f,Y = %f,Z= %f,R= %f,P= %f,Y= %f",ob[0],ob[1],ob[2],ob[3],ob[4],ob[5]);
		printf("Converge Euler to Quarternian \n");
		q.setRPY(ob[3]*M_PI/180,ob[4]*M_PI/180,ob[5]*M_PI/180);
		q=q.normalize();
		msg.x = ob[0];
		msg.y = ob[1];
		msg.z = ob[2];
		msg.orx = q[0];
		msg.ory = q[1];
		msg.orz = q[2];
		msg.orw = q[3];
		msg1.move = 1;
		msg1.object = 1;
		msg1.target = 0;
		msg2.converge = 0;
		pub.publish(msg);
		pub1.publish(msg1);
		pub2.publish(msg2);
		}
		else if(chg==1){
		ROS_INFO_NAMED("Target_in", "Converse Target_coordinate : X = %f,Y = %f,Z= %f,R= %f,P= %f,Y= %f",tr[0],tr[1],tr[2],tr[3],tr[4],tr[5]);
		printf("Converge Euler to Quarternian \n");
		q.setRPY(tr[3]*M_PI/180,tr[4]*M_PI/180,tr[5]*M_PI/180);
		q=q.normalize();
		msg.x = tr[0];
		msg.y = tr[1];
		msg.z = tr[2];
		msg.orx = q[0];
		msg.ory = q[1];
		msg.orz = q[2];
		msg.orw = q[3];
		msg1.move = 1;
		msg1.object = 0;
		msg1.target = 1;
		msg3.change = 0;
		pub.publish(msg);
		pub1.publish(msg1);
		pub3.publish(msg3);
		}
		loop_rate.sleep();
		//ros::spin();
	}
	ros::shutdown();
	return 0;
}
