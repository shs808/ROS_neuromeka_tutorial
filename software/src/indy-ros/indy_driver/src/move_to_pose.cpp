#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_visual_tools/moveit_visual_tools.h>
#include <geometry_msgs/Pose.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <string>
#include <stdio.h>
#include <indy_driver/IndyMsg.h>
#include <indy_driver/moveon.h>
#include <indy_driver/GripperSg.h>
#include <indy_driver/CameraDetect.h>
#include <sensor_msgs/JointState.h>
double d[7]={0.4,0.5,0.9,sqrt(2)/2,sqrt(2)/2,sqrt(2)/2,sqrt(2)/2};
double mv[4]= {0,0,0,0};
#define JOINT_DOF 6

void msgcallback(const indy_driver::IndyMsg::ConstPtr& msg){
	d[0]=msg->x ;
	d[1]=msg->y ;
	d[2]=msg->z ;
	d[3]=msg->orx ;
	d[4]=msg->ory ;
	d[5]=msg->orz ;
    d[6]=msg->orw ;
}

void msgcallback1(const indy_driver::moveon::ConstPtr& msg1){
    mv[0]= msg1->move;
    mv[1]= msg1->object;
    mv[2]= msg1->target;
}


int main(int argc, char **argv)
{   
    
    ros::init(argc, argv, "move_to_pose");
    ros::NodeHandle n4,n5,n8;
    ros::AsyncSpinner spinner(1);
    spinner.start();
    int tg = 0;
    // Initialising and defining the planning group for move_base
    static const std::string PLANNING_GROUP = "indy10";
    moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
    // Raw pointers are frequently used to refer to the planning group for improved performance.
    const robot_state::JointModelGroup *joint_model_group =
        move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);
    // Place code here.
    ros::Subscriber sub = n4.subscribe<indy_driver::moveon>("Go_to_pose", 10, msgcallback1);
    ros::Subscriber sub1 = n8.subscribe<indy_driver::IndyMsg>("Move_coordinate", 10, msgcallback);
    ros::Publisher pub = n4.advertise<indy_driver::moveon>("Go_to_pose", 10);
    ros::Publisher pub1 = n5.advertise<indy_driver::GripperSg>("Gripper", 10);
  //  ros::Publisher pub3 = n1.advertise<indy_driver::CameraDetect>("CameraDetect", 10);
    indy_driver::moveon msg;
    indy_driver::GripperSg msg1;
    ros::Rate loop_rate(10);
    geometry_msgs::Pose target_pose;


    while (ros::ok()){
        loop_rate.sleep();
        if(mv[0]==1){
            if(tg == 0){
            target_pose.position.x = d[0];
            target_pose.position.y = d[1];
            target_pose.position.z = d[2]+0.10;
            target_pose.orientation.x = d[3];
            target_pose.orientation.z = d[4];
            target_pose.orientation.y = d[5];
            target_pose.orientation.w = d[6];
            move_group.setPoseTarget(target_pose);
            //ROS_INFO_NAMED("Section1", "***********Go target**********");
           // ROS_INFO_NAMED("move_to_pos", "Setting the target position to x=%g, y=%g, z=%g",target_pose.position.x, target_pose.position.y, target_pose.position.z);
            //ROS_INFO_NAMED("move_to_ori", "Setting the orientation to x=%g, y=%g, z=%g, w=%g",target_pose.orientation.x, target_pose.orientation.y, target_pose.orientation.z, target_pose.orientation.w);
            moveit::planning_interface::MoveGroupInterface::Plan my_plan;
            bool success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);  
            move_group.move();
            tg = 1;
            }
            if(tg == 1){
            target_pose.position.x = d[0];
            target_pose.position.y = d[1];
            target_pose.position.z = d[2];
            target_pose.orientation.x = d[3];
            target_pose.orientation.z = d[4];
            target_pose.orientation.y = d[5];
            target_pose.orientation.w = d[6];
            move_group.setPoseTarget(target_pose);
           // ROS_INFO_NAMED("Section2", "*********Close target**********");
            //ROS_INFO_NAMED("move_to_pos", "Setting the target position to x=%g, y=%g, z=%g",target_pose.position.x, target_pose.position.y, target_pose.position.z);
           // ROS_INFO_NAMED("move_to_ori", "Setting the orientation to x=%g, y=%g, z=%g, w=%g",target_pose.orientation.x, target_pose.orientation.y, target_pose.orientation.z, target_pose.orientation.w);
            moveit::planning_interface::MoveGroupInterface::Plan my_plan;
            bool success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);  
            move_group.move();
            tg = 0;
            }
            if(mv[1]==1) msg1.grip = 1;
            else if(mv[2]==1) msg1.grip = 2;
            msg.move = 0;
            pub.publish(msg);
            pub1.publish(msg1);


        }
        loop_rate.sleep();
        //ros::spin();
    }
    ros::shutdown();
    return 0;
}