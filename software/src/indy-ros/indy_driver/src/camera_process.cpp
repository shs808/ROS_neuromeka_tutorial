
#include <string>
#include <stdio.h>
#include <ros/ros.h>
#include <indy_driver/CameraDetect.h>
#include <indy_driver/ObjectSet.h>
#include <indy_driver/TargetSet.h>
#include <indy_driver/Converseon.h>
#include <tf/tf.h>
//double ob[6]={0.4,0.5,0.9,0,181,91};
//double tr[6]={0.4,0.5,0.9,0,181,91};
double cr=0;
double camcord[4]={0.15,0.475,0.4,0.475};
double cvr=0;
#define JOINT_DOF 6

void msgcallback(const indy_driver::CameraDetect::ConstPtr& msg){
	cr=msg->on ;
    camcord[0]=msg->obX;
    camcord[1]=msg->obY;
    camcord[2]=msg->trX;
    camcord[3]=msg->trY;

}
int main(int argc, char **argv)
{   
    
    ros::init(argc, argv, "camera_process");
    ros::NodeHandle n1, n2, n3,n7;
    ros::AsyncSpinner spinner(1);
    spinner.start();
    ros::Subscriber sub = n1.subscribe<indy_driver::CameraDetect>("CameraDetect", 10, msgcallback);
    ros::Publisher pub2 = n1.advertise<indy_driver::CameraDetect>("CameraDetect", 10);
    ros::Publisher pub = n2.advertise<indy_driver::ObjectSet>("ObjectSet", 10);
    ros::Publisher pub1 = n3.advertise<indy_driver::TargetSet>("TargetSet", 10);
    ros::Publisher pub3 = n7.advertise<indy_driver::Converseon>("Converseon", 10);
    indy_driver::ObjectSet msg;
    indy_driver::TargetSet msg1;
    indy_driver::CameraDetect msg2;
    indy_driver::Converseon msg3;
    ros::Rate loop_rate(10);
    //trig[0]= 0;
    //float trig = 0;

    while (ros::ok()){
       // ROS_INFO_NAMED("trig", "trig111=%f, %f, %f, %f, %f, %f",msg1.camdtc,msg1.camgoal,msg1.moveon,msg1.sethome,msg1.gripper,msg1.movecr);
       // ROS_INFO_NAMED("trig", "trigdasd=%f, %f, %f, %f, %f, %f",trig[0],trig[1],trig[2],trig[3],trig[4],trig[5]);
        if(cr==1){
            ROS_INFO_NAMED("Object_coordinate", "olo");
            msg.ox = camcord[0];
            msg.oy = camcord[1];
            msg.oz = 0.610;
            msg.oR = -1;
            msg.oP = 179;
            msg.oY = 181;
            ROS_INFO_NAMED("Object_coordinate", "Object_coordinate : X = %f,Y = %f,Z= %f,R= %f,P= %f,Y= %f",msg.ox,msg.oy,msg.oz,msg.oR,msg.oP,msg.oY);

            msg1.tx = camcord[2];
            msg1.ty = camcord[3];
            msg1.tz = 0.65;
            msg1.tR = -1;
            msg1.tP = 179;
            msg1.tY = 181;
            ROS_INFO_NAMED("Target_coordinate", "Target_coordinate : X = %f,Y = %f,Z= %f,R= %f,P= %f,Y= %f",msg1.tx,msg1.ty,msg1.tz,msg1.tR,msg1.tP,msg1.tY);

            msg2.on = 0;
            msg3.converge = 1;

        	pub.publish(msg);
            pub1.publish(msg1);
            pub2.publish(msg2);
            pub3.publish(msg3);

        }
        loop_rate.sleep();
        //ros::spin();
    }
    ros::shutdown();
    return 0;
}