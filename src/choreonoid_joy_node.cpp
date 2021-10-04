#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <cnoid/Joystick>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "choreonoid_joy");

    ros::NodeHandle nh("~");
    string device;
    nh.getParam("dev", device);
    cnoid::Joystick joystick(device.c_str());
    
    ros::NodeHandle node;
    ros::Publisher publisher = node.advertise<sensor_msgs::Joy>("joy", 30);
    ros::Rate loop_rate(60);
    int seq = 0;
    bool stateChanged = false;

    joystick.sigButton().connect(
        [&](int, bool){ stateChanged = true; });
    joystick.sigAxis().connect(
        [&](int, double){ stateChanged = true; });

    if(!joystick.isReady()){
        cout << "Joystick is not ready." << endl;
    }
    bool isBeforeInitialReading = true;

    while(ros::ok()){
        if(!joystick.isReady()){
            if(!joystick.makeReady()){
                usleep(500000);
                continue;
            }
        }
        if(isBeforeInitialReading){
            cout << "Joystick \"" << joystick.device() << "\" is ready." << endl;
            isBeforeInitialReading = false;
        }
        joystick.readCurrentState();
        if(stateChanged){
            sensor_msgs::Joy joy;
            joy.header.seq = seq++;
            joy.header.stamp = ros::Time::now();
            const int numAxes = joystick.numAxes();
            joy.axes.resize(numAxes);
            for(int i=0; i < numAxes; ++i){
                joy.axes[i] = joystick.getPosition(i);
            }
            const int numButtons = joystick.numButtons();
            joy.buttons.resize(numButtons);
            for(int i=0; i < numButtons; ++i){
                joy.buttons[i] = joystick.getButtonState(i) ? 1 : 0;
            }
            publisher.publish(joy);
            stateChanged = false;
        }
        loop_rate.sleep();
    }
    return 0;
}
