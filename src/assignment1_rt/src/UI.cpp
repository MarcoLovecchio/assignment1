#include "ros/ros.h"
#include "turtlesim/Spawn.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv){
	ros::init(argc, argv, "UI_node");
	ros::NodeHandle nh;
	
	ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");
	turtlesim::Spawn new_turtle;
	new_turtle.request.x = 2.0;
	new_turtle.request.y = 2.0;
	new_turtle.request.theta = 0.0;
	new_turtle.request.name = "turtle2";
	client.waitForExistence();
	client.call(new_turtle);
	
	ros::Publisher pub1 = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);
	ros::Publisher pub2 = nh.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 1);
	
	ros::Rate loop_rate(1);
	geometry_msgs::Twist new_vel;
	
	int selected_turtle;
	bool check = false;
	
	while (ros::ok()){
		do{
			std::cout<<"Chose the turtle to control (1 or 2): ";
			std::cin>>selected_turtle;
		
			if(selected_turtle == 1 || selected_turtle == 2){
				check = true;
			}else{
				std::cout<<"Turtle "<<selected_turtle<<"doesn't exis";
			}
		}while(!check);
		
		std::cout<<"X linear velocity: ";
		std::cin>>new_vel.linear.x;
		std::cout<<"Y linear velocity: ";
		std::cin>>new_vel.linear.y;
		std::cout<<"Z angular velocity: ";
		std::cin>>new_vel.angular.z;
	
		if(selected_turtle == 1){
			pub1.publish(new_vel);
		}else if(selected_turtle == 2){
			pub2.publish(new_vel);
		}
	
		check = false;
		ros::spinOnce;
		loop_rate.sleep();
	}
	
	return 0;
}
