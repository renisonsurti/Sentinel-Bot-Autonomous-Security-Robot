#include <Servo.h> 
#include <NewPing.h> 
#include <DHT.h> 
#define SERVO_PIN 3 
#define ULTRASONIC_SENSOR_TRIG 11 
#define ULTRASONIC_SENSOR_ECHO 12 
#define MAX_REGULAR_MOTOR_SPEED 75 
#define MAX_MOTOR_ADJUST_SPEED 150 
#define DISTANCE_TO_CHECK 30 
#define ledPin 6 
#define sensorPin A0 
#define DHTPIN 7      
#define DHTTYPE DHT22    
DHT dht(DHTPIN, DHTTYPE);  
int enableRightMotor=5; 
int rightMotorPin1=7; 
int rightMotorPin2=8; 
int enableLeftMotor=6; 
int leftMotorPin1=9; 
int leftMotorPin2=10; 
NewPing mySensor(ULTRASONIC_SENSOR_TRIG, ULTRASONIC_SENSOR_ECHO, 
400); 
Servo myServo; 
int ledPin = 13;                 
int inputPin = 2;     
int pirState = LOW;            
int val = 0; 
int chk; 
float hum;   
float temp;  
 
void setup() 
{ 
  pinMode(enableRightMotor,OUTPUT); 
  pinMode(rightMotorPin1,OUTPUT); 
  pinMode(rightMotorPin2,OUTPUT); 
   
  pinMode(enableLeftMotor,OUTPUT); 
  pinMode(leftMotorPin1,OUTPUT); 
  pinMode(leftMotorPin2,OUTPUT); 
 
  myServo.attach(SERVO_PIN); 
  myServo.write(90); 
  rotateMotor(0,0);    
  pinMode(ledPin, OUTPUT);       
  pinMode(inputPin, INPUT);     
  Serial.begin(9600); 
  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin, LOW); 
  dht.begin(); 
} 
 
void loop() 
{
      int distance = mySensor.ping_cm(); 
 
  if (distance > 0 && distance < DISTANCE_TO_CHECK) 
  { 
    
    rotateMotor(0, 0); 
    delay(500);   
        
    
    rotateMotor(-MAX_MOTOR_ADJUST_SPEED, 
MAX_MOTOR_ADJUST_SPEED);         
    delay(200); 
     
 
    rotateMotor(0, 0); 
    delay(500); 
     
     
    myServo.write(180); 
    delay(500); 
 
    int distanceLeft = mySensor.ping_cm();     
 
    myServo.write(0);     
    delay(500);     
 
    int distanceRight = mySensor.ping_cm(); 
 
   
    myServo.write(90);  
    delay(500);      
     if (distanceLeft == 0 ) 
    { 
      rotateMotor(MAX_MOTOR_ADJUST_SPEED, -MAX_MOTOR_ADJUST_SPEED); 
      delay(200); 
    } 
    else if (distanceRight == 0 ) 
    { 
      rotateMotor(-MAX_MOTOR_ADJUST_SPEED, MAX_MOTOR_ADJUST_SPEED); 
      delay(200); 
    } 
    else if (distanceLeft >= distanceRight) 
    { 
      rotateMotor(MAX_MOTOR_ADJUST_SPEED, -MAX_MOTOR_ADJUST_SPEED); 
      delay(200); 
    } 
    else 
    { 
      rotateMotor(-MAX_MOTOR_ADJUST_SPEED, MAX_MOTOR_ADJUST_SPEED); 
      delay(200);       
    } 
    rotateMotor(0, 0);     
    delay(200);      
  } 
  else 
  { 
    rotateMotor(MAX_REGULAR_MOTOR_SPEED, 
MAX_REGULAR_MOTOR_SPEED); 
  } 
}
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) 
{ 
  if (rightMotorSpeed < 0) 
  { 
    digitalWrite(rightMotorPin1,LOW); 
    digitalWrite(rightMotorPin2,HIGH);     
  } 
  else if (rightMotorSpeed >= 0) 
  { 
    digitalWrite(rightMotorPin1,HIGH); 
    digitalWrite(rightMotorPin2,LOW);       
  } 
 
  if (leftMotorSpeed < 0) 
  { 
    digitalWrite(leftMotorPin1,LOW); 
    digitalWrite(leftMotorPin2,HIGH);     
  } 
  else if (leftMotorSpeed >= 0) 
  { 
    digitalWrite(leftMotorPin1,HIGH); 
    digitalWrite(leftMotorPin2,LOW);       
  } 
 
  analogWrite(enableRightMotor, abs(rightMotorSpeed)); 
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));   
 
  val = digitalRead(inputPin);   
  if (val == HIGH) {           
    digitalWrite(ledPin, HIGH);  
    if (pirState == LOW) { 
      Serial.println("Motion detected!"); 
      pirState = HIGH; 
    } 
  } else { 
    digitalWrite(ledPin, LOW);  
    if (pirState == HIGH){ 
      Serial.println("Motion ended!"); 
      pirState = LOW; 
    } 
  } 
  Serial.print("Analog output: "); 
  Serial.println(readSensor()); 
  delay(500); 
} 
int readSensor() { 
  unsigned int sensorValue = analogRead(sensorPin);  
  unsigned int outputValue = map(sensorValue, 0, 1023, 0, 255);  
  if (outputValue > 65) 
    analogWrite(ledPin, outputValue);  
  else 
    digitalWrite(ledPin, LOW); 
  return outputValue;            
      delay(2000); 
    hum = dht.readHumidity(); 
    temp= dht.readTemperature(); 
    Serial.print("Humidity: "); 
    Serial.print(hum); 
    Serial.print(" %, Temp: "); 
    Serial.print(temp); 
    Serial.println(" Celsius"); 
delay(10000); 
}