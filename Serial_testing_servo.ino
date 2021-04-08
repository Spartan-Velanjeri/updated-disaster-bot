#include <Servo.h>

Servo myservo;
Servo myservo1;

int pos = 90;
int pos1 = 90;
String command;

void setup() {
  // put your setup code here, to run once:

myservo.attach(10);
myservo1.attach(9); //End effector one

myservo.write(pos);
myservo1.write(pos1);

Serial.begin(9600);
Serial.println("Type your commands");

}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()){
    command = Serial.readStringUntil('\n');

    if(command.equals("a")){
      counterclockwise();
    }
    else if(command.equals("d")){
      clockwise();
    }
    else if(command.equals("s")){
      station();
    }
        if(command.equals("j")){
      counterclockwise1();
    }
    else if(command.equals("l")){
      clockwise1();
    }
    else if(command.equals("k")){
      station1();
    }
  }

}

void counterclockwise(){
  if(pos>0){
    pos = pos - 5;
    myservo.write(pos);
    delay(15);
  }
  else{
    Serial.println("Can't go below 0 boss");
  }
}

void counterclockwise1(){
  if(pos1>15){
    pos1 = pos1 - 5;
    myservo1.write(pos1);
    delay(15);
  }
  else{
    Serial.println("Can't go below 15 boss");
  }
}

void clockwise(){
  if(pos<180){
    pos = pos + 5;
    myservo.write(pos);
    delay(15);
  }
  else{
    Serial.println("Can't go above 180 boss");
  }
}


void clockwise1(){
  if(pos1<170){
    pos1 = pos1 + 5;
    myservo1.write(pos1);
    delay(15);
  }
  else{
    Serial.println("Can't go above 170 boss");
  }
}

void station(){
  Serial.println(" You are currently at ");
  Serial.println(pos);
}

void station1(){
  Serial.println(" You are currently at ");
  Serial.println(pos1);
}
