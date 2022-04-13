#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_visual_tools/moveit_visual_tools.h>
#include <geometry_msgs/Pose.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <string>
#include <stdio.h>
#include <indy_driver/Cameratrg.h>
#include <sensor_msgs/JointState.h>
#include <indy_driver/Gohome.h>
#define JOINT_DOF 6
double homest = 0;

void msgcallback(const indy_driver::Gohome::ConstPtr& msg){
	homest=msg->gohome ;

}

int main(int argc, char **argv)
{   
    
    ros::init(argc, argv, "SetHome");
    ros::NodeHandle n1,n2;
    ros::AsyncSpinner spinner(1);
    spinner.start();
    // Initialising and defining the planning group for move_base
    static const std::string PLANNING_GROUP = "indy10";
    moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
    // Raw pointers are frequently used to refer to the planning group for improved performance.
    const robot_state::JointModelGroup *joint_model_group =
    move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);
    // Place code here.
    ros::Subscriber sub1 = n2.subscribe<indy_driver::Gohome>("Hometrg", 10, msgcallback);
    ros::Publisher pub = n1.advertise<indy_driver::Cameratrg>("Cameratrg", 10);
    ros::Publisher pub1 = n2.advertise<indy_driver::Gohome>("Hometrg", 10);
    indy_driver::Cameratrg msg;
    indy_driver::Gohome msg1;
    ros::Rate loop_rate(5);

    while (ros::ok()){
        if(homest ==0){
        sensor_msgs::JointState joint_state;
    	joint_state.name.resize(JOINT_DOF);
		joint_state.position.resize(JOINT_DOF);

		joint_state.name[0] = "joint0";
		joint_state.position[0] = 0;
		joint_state.name[1] = "joint1";
		joint_state.position[1] = -30*M_PI/180;
		joint_state.name[2] = "joint2";
		joint_state.position[2] = 90*M_PI/180;
		joint_state.name[3] = "joint3";
		joint_state.position[3] = 0*M_PI/180;
		joint_state.name[4] = "joint4";
		joint_state.position[4] = 90*M_PI/180;
		joint_state.name[5] = "joint5";
		joint_state.position[5] = 0;
        ROS_INFO_NAMED("Section3", "*********Set Home Pose**********");
        move_group.setJointValueTarget(joint_state);
        move_group.move();
        msg.on = 1 ;
        homest = 1; 
        msg1.gohome = 1; 
        pub.publish(msg);
        ROS_INFO_NAMED("SetHome", "Complete Home Pose, Camera detect ON (%f)",msg.on); 
        }
        //ros::spin();
    }
    ros::shutdown();
    return 0;
}