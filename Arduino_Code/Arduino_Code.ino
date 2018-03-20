#include <SoftwareSerial.h>

SoftwareSerial mySerial(19, 18); // RX, TX
#define trigPin 13
#define echoPin 12
const int input1 = 11; //Number of Motor Input 1 Pin
const int input2 = 10; //Number of Motor Input 2 Pin
const int input3 = 9; //Number of Motor Input 3 Pin
const int input4 = 8; //Number of Motor Input 4 Pin
float dur1,dur2, dis1, dis2, time1, time2, velocity; // Duration varible stores time duration taken by ultrasonic and Distance variable stores distance

void setup() {
  Serial.begin (9600); // Begin the Serial Monitor at 9600 Baud
  mySerial.begin(9600);
  
  pinMode(trigPin, OUTPUT); // Initialize Trigger Pin
  pinMode(echoPin, INPUT); // Initialize Echo Pin
  pinMode(input1, OUTPUT); //Initialize Input 1 Pin
  pinMode(input2, OUTPUT); //Initialize Input 2 Pin
  pinMode(input3, OUTPUT); //Initialize Input 3 Pin
  pinMode(input4, OUTPUT); //Initialize Input 4 Pin
  
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH); // Set Trigger Pin High
  delay(5); // Delay
  digitalWrite(trigPin, LOW); // Set Trigger Pin Low
  dur2 = pulseIn(echoPin, HIGH); // Set Echo Pin High to set time to variable
  dis2 = (dur1/2) / 29.1; // Convert time into distance
}

void loop() {
  dis1 = dis2;
  time1 = millis();
  Serial.print(dis1);
  Serial.print(" ");
  delay(100);
  
  digitalWrite(trigPin, HIGH); // Set Trigger Pin High
  delay(5); // Delay
  digitalWrite(trigPin, LOW); // Set Trigger Pin Low
  dur2 = pulseIn(echoPin, HIGH); // Set Echo Pin High to set time to variable
  dis2 = (dur2/2) / 29.1; // Convert time into distance
  time2 = millis();
  Serial.print(dis2);
  Serial.write(int(dis2));
  Serial.print(" ");
  Serial.print(time2);
  Serial.print(" ");
  
  mySerial.write(int(dis2));  
  velocity = (dis1-dis2)/((time2-time1)*0.001);
  Serial.print(velocity);
  Serial.println(" cm/s");
  
  if(dis2<(velocity*velocity/800) || dis2<10){
    //Stops Motor Driving
    digitalWrite(input1, LOW); //Write Analog value to Input 1
    digitalWrite(input2, LOW); //Write Analog value to Input 2
    digitalWrite(input3, LOW); //Write Analog value to Input 3
    digitalWrite(input4, LOW); //Write Analog value to Input 4
  }
  else{
    //Starts Motor Driving
    digitalWrite(input1, HIGH); //Write Analog value to Input 1
    digitalWrite(input2, LOW); //Write Analog value to Input 2
    digitalWrite(input3, HIGH); //Write Analog value to Input 3
    digitalWrite(input4, LOW); //Write Analog value to Input 4
  }
  delay(100);
}
