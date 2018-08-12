#include <ros/ros.h>
#include <sensor_msgs/Joy.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "choreonoid_joy");
    ros::NodeHandle node;
    os::Publisher publisher = n.advertise<sensor_msgs::Joy>("joy", 1000);
    while(ros::ok()){
        sensor_msgs::Joy joy;
        publisher.publish(joy);
    }
    return 0;
}
