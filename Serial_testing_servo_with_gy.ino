#include <Servo.h>
#include <Wire.h>

const int MPU=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;


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

  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  

Serial.begin(9600);
Serial.println("Type your commands");

}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()){
    command = Serial.readStringUntil('\n');

    if(command.equals("a")){
      gyroblast();
      counterclockwise();
      gyroblast();
    }
    else if(command.equals("d")){
      gyroblast();
      clockwise();
      gyroblast();
    }
    else if(command.equals("s")){
      gyroblast();
      station();
      gyroblast();
    }
        if(command.equals("j")){
          gyroblast();
      counterclockwise1();
      gyroblast();
    }
    else if(command.equals("l")){
      gyroblast();
      clockwise1();
      gyroblast();
    }
    else if(command.equals("k")){
      gyroblast();
      station1();
      gyroblast();
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
void gyroblast(){
  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();  
  
  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = "); Serial.println(AcZ); 
  
  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);
  Serial.println(" ");
  delay(333);
}
