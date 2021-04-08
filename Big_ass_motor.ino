////////////////////////
int motor1 = 6;
int dir = 8;
String command;
int pos = 60;
int enc1 = A0;
int enc2 = A1;
int a = 0;
int b = 0;

/////////////////////////
#include <Servo.h>

Servo myservo;
Servo myservo1;


void setup() {
  //Declaring LED pin as output
  pinMode(motor1, OUTPUT);
  //pinMode(brake1,OUTPUT);
  pinMode(dir,OUTPUT);
  pinMode(enc1,INPUT);
  pinMode(enc2,INPUT);

//////////////////////////

myservo.attach(9);
myservo1.attach(10);
myservo.write(90);
myservo1.write(90);

//////////////////////////
Serial.begin(9600);
Serial.println("Type your commands");

}

void loop() {
  
  if(Serial.available()){
    command = Serial.readStringUntil('\n');

    if(command.equals("down")){
      ascend();
      reader();
    }
    else if(command.equals("up")){
      descend();
      reader();
    }
    else if(command.equals("stop")){
      stoprobot();
      reader();
    }
    else if(command.equals("side")){
      sideways();
      reader();
    }
  }
}

void ascend(){
  digitalWrite(dir,HIGH);
  analogWrite(motor1,25);
  delay(1000); //460
  analogWrite(motor1,0);

/////////////////////////////////
for (pos = 90; pos <= 125; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos); 
    delay(15);                       // waits 15ms for the servo to reach the position
  }
      for (pos = 90; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos);// tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

    for (pos = 120; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);// tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 125; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos); 
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void descend(){
  digitalWrite(dir,LOW);
  analogWrite(motor1,25);
  delay(1000);
  analogWrite(motor1,0);

/////////////////////////////////

      for (pos = 90; pos <= 125; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos); 
    delay(15);                       // waits 15ms for the servo to reach the position
  }
      for (pos = 90; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos);// tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

    for (pos = 120; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);// tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 125; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos); 
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
  
void stoprobot(){
  digitalWrite(dir,LOW);
  analogWrite(motor1,0);
}

void sideways(){
for (pos = 90; pos <= 125; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos); 
    delay(15);                       // waits 15ms for the servo to reach the position
  }
      for (pos = 90; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos);// tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

    for (pos = 120; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);// tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 125; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos); 
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void reader(){
  a = analogRead(enc1);
  b = analogRead(enc2);
  Serial.println(a);
  Serial.println(b);

}
