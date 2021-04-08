/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

#include <ros.h>
#include <sensor_msgs/JointState.h>
#include <Servo.h>
int pos = 0;
int angle1 = 0;
float alpha = 0;
int angle2 = 0;
float beta = 0;
float gamma = 0;
int angle3 = 0;

ros::NodeHandle  nh;
Servo myservo1; Servo myservo2; Servo myservo3;

void messageCb( const sensor_msgs::JointState& joint_states){
  
 if(1){
    alpha = joint_states.position[0];
    beta = joint_states.position[1];
    gamma = joint_states.position[2];
     
    digitalWrite(13,HIGH);
    //int angle1 = ((alpha+0.7854)*(90/1.5708)); 
    int angle2 = (57.3*beta)+75; // Used Matlab for formula
    int angle3 = (57.3*gamma)+115;


    //myservo1.write(angle1);
    myservo2.write(angle2);
    myservo3.write(angle3);
    
    digitalWrite(13,LOW);
    delay(1);
 }
}

ros::Subscriber<sensor_msgs::JointState> sub("joint_states", &messageCb );

void setup()
{ 
  pinMode(13, OUTPUT);
  
  nh.initNode();
  nh.subscribe(sub);
  myservo1.attach(8);
  myservo2.attach(9);
  myservo3.attach(10);
  myservo2.write(75);
  myservo3.write(115);
}
  
void loop()
{  
  nh.spinOnce();
  delay(1);
}
