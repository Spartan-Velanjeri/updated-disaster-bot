int motor1 = 6;
int dir = 8;
String command;


void setup() {
  // put your setup code here, to run once:
pinMode(motor1,OUTPUT);
pinMode(dir,OUTPUT);
Serial.begin(9600);
Serial.println("Type your commands");

}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()){
    command = Serial.readStringUntil('\n');

    if(command.equals("down")){
      ascend();

    }
    else if(command.equals("up")){
      descend();

    }
    
}
}

void ascend() //goes up
{
  digitalWrite(dir,HIGH);
  analogWrite(motor1,25);
  delay(2000);
  analogWrite(motor1,0);
}
void descend() //goes down
{
  digitalWrite(dir,LOW);
  analogWrite(motor1,25);
  delay(2000);
  analogWrite(motor1,0);
}
