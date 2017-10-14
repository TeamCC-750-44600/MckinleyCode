#include <Servo.h>
Servo myServo;
int pos = 20;
//Motor 1
int PWMA = 3;
int MotorA = 12;
int BrakeA = 9; 
//Motor 2
int PWMB = 11;
int MotorB = 13;
int BrakeB = 8; 
boolean reset=false;
//variable for middle, right and left distance
int middle_distance;
int right_distance;
int left_distance;

//pins for Ultrasonic sensors
#define trigPin  2
#define echoPin  5

// function to calucate distance using ultasonic sensor
int calculate_distance()
{
  int duration = 0;
  int distance = 0;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= (duration/2) /29.1;  // convert to cm
  Serial.println(distance + " cm");
  return distance;
}

void turn_right()
{
  digitalWrite(BrakeA, HIGH);
  digitalWrite(MotorA, HIGH);
  analogWrite(PWMA, 200);
  digitalWrite(MotorB, HIGH);
  digitalWrite(BrakeB, LOW);
  analogWrite(PWMB, 190);
  delay(500);
  digitalWrite(MotorA, HIGH);
  digitalWrite(BrakeA, HIGH);
  digitalWrite(MotorB, HIGH);
  digitalWrite(BrakeB, HIGH);
  Serial.println("turned right");
}
void turn_left()
{
  digitalWrite(BrakeA, LOW);
  digitalWrite(MotorA, HIGH);
  analogWrite(PWMA, 200);
  digitalWrite(MotorB, HIGH);
  digitalWrite(BrakeB, HIGH);
  analogWrite(PWMB, 190);
  delay(500);
  digitalWrite(MotorA, HIGH);
  digitalWrite(BrakeA, HIGH);
  digitalWrite(MotorB, HIGH);
  digitalWrite(BrakeB, HIGH);
  Serial.println("turned left");
}

void move_forward()
{
  digitalWrite(BrakeA, LOW);
  digitalWrite(MotorA, HIGH);
  analogWrite(PWMA, 200);
  digitalWrite(MotorB, HIGH);
  digitalWrite(BrakeB, LOW);
  analogWrite(PWMB, 190);
  delay(4000);
  digitalWrite(MotorA, HIGH);
  digitalWrite(BrakeA, HIGH);
  digitalWrite(MotorB, HIGH);
  digitalWrite(BrakeB, HIGH);
  Serial.println("moved forward");
}


void setup() 
{
  pinMode(MotorA, OUTPUT);
  pinMode(BrakeA, OUTPUT);
  pinMode(MotorB, OUTPUT);
  pinMode(BrakeB, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  myServo.attach(16);
  Serial.begin(9600);
}


void loop() 
{
  if(reset==false)
  {
    delay(1000);  
    for(pos = 25; pos < 105; pos+= 1)
    {
      myServo.write(pos);
      Serial.println(pos-25);
      delay(10);
    }
    reset=true;
    Serial.println("Have reset");
  }
  middle_distance = calculate_distance();
  for (pos = 105; pos < 205; pos += 1) 
  {
    myServo.write(pos);   
    Serial.println(pos-25);
  }
  
  left_distance = calculate_distance();
  for (pos = 205; pos > 25; pos -= 1) 
  { 
    myServo.write(pos);  
    Serial.println(pos-25);   
  }
  right_distance = calculate_distance();
  
  for (pos = 25; pos < 105; pos += 1) 
  {
      myServo.write(pos);   
      Serial.println(pos-25);   
  }

  if(left_distance > 120 || right_distance > 120 || middle_distance > 120)
  {
    if(left_distance > right_distance && left_distance > middle_distance)
    {
      turn_left();
    }
    else if(right_distance > left_distance && right_distance > middle_distance)
    {
      turn_right();
    }
    else if(middle_distance > left_distance && middle_distance > right_distance)
      move_forward();
  }
  

}
