#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

//Right motor
int ENA=12; 
int IN1=27;
int IN2=14;
//Left motor
int IN3=26;
int IN4=25;
int ENB=33;

#define MAX_MOTOR_SPEED 255

const int PWMFreq = 1000; /* 1 KHz */
const int PWMResolution = 8;
const int rightMotorPWMSpeedChannel = 4;
const int leftMotorPWMSpeedChannel = 5;

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  if (rightMotorSpeed < 0)
  {
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);      
  }
  else
  {
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);      
  }
  
  if (leftMotorSpeed < 0)
  {
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);    
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);      
  }
  else
  {
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);      
  }
  
  ledcWrite(rightMotorPWMSpeedChannel, abs(rightMotorSpeed));
  ledcWrite(leftMotorPWMSpeedChannel, abs(leftMotorSpeed));  
}

void setUpPinModes()
{
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  //Set up PWM for speed
  ledcSetup(rightMotorPWMSpeedChannel, PWMFreq, PWMResolution);
  ledcSetup(leftMotorPWMSpeedChannel, PWMFreq, PWMResolution);  
  ledcAttachPin(ENA, rightMotorPWMSpeedChannel);
  ledcAttachPin(ENB, leftMotorPWMSpeedChannel); 

  rotateMotor(0,0); 
}

void setup()
{
  setUpPinModes();
  Dabble.begin("ESP32_4WD_08"); 
}

void loop()
{
  int rightMotorSpeed=0;
  int leftMotorSpeed=0;
  Dabble.processInput();
  if (GamePad.isUpPressed())
  {
    rightMotorSpeed = -MAX_MOTOR_SPEED;
    leftMotorSpeed = -MAX_MOTOR_SPEED;
  }

  if (GamePad.isDownPressed())
  {
    rightMotorSpeed = MAX_MOTOR_SPEED;
    leftMotorSpeed = MAX_MOTOR_SPEED;
  }

  if (GamePad.isLeftPressed())
  {
    rightMotorSpeed = MAX_MOTOR_SPEED;
    leftMotorSpeed = -MAX_MOTOR_SPEED;
  }

  if (GamePad.isRightPressed())
  {
    rightMotorSpeed = -MAX_MOTOR_SPEED;
    leftMotorSpeed = MAX_MOTOR_SPEED;
  }

  rotateMotor(rightMotorSpeed, leftMotorSpeed);
}