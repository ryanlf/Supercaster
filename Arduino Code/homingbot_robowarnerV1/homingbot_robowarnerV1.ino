//Code written by Warner K. of www.robowarner.com
//Made for the Radio Direction Finding Robot at www.robowarner.com/robot/rdfbot
//You are free to modify, distribute and store this code. 
//
//USE THIS CODE AT YOUR OWN RISK!
//I am NOT liable for any harm that results from the use of this code. 
//
// Code is based off of the original BASIC for the robot, so it has room for improvement. :)

//Defines (Constants)
#define buffering 25 //what counts as straight ahead? If too small, the robot will jitter. If too large the robot will drive away from the transmitter
//pinout
#define ANT_WAVEFORM_OUT 8 // set output pin
#define SPEAKER_FROM_WALKIETALKIE A1 //set input pin
#define CALIBRATE_IN 48
#define LEFT_MOTOR_PIN  9
#define RIGHT_MOTOR_PIN 10

//Variables
uint16_t caliset = 0;
uint16_t voltage = 0;


//includes
#include <EEPROM.h>

//start program
void setup() {
analogReference(DEFAULT);
Serial.begin(9600); //begin serial monitor output, remove if you don't want it
delay(6000); // I put this delay here so the robot won't move until the walkie talkie has had time to turn on.
pinMode(ANT_WAVEFORM_OUT, OUTPUT);
pinMode(SPEAKER_FROM_WALKIETALKIE, INPUT);
pinMode(LEFT_MOTOR_PIN,OUTPUT);
pinMode(RIGHT_MOTOR_PIN,OUTPUT);
pinMode(CALIBRATE_IN, INPUT);
digitalWrite(CALIBRATE_IN, HIGH); // enable internal pullup resistor

//read calibration word from EEPROM
byte HByte =  EEPROM.read(1);
byte LByte =  EEPROM.read(2);
caliset = word(HByte, LByte);
Serial.print("EEPROM Calibration number: ");
Serial.print(caliset);
Serial.println(" If you haven't calibrated yet, you need to for it to work");

if (digitalRead(CALIBRATE_IN) == LOW){ // used for calibratingu
digitalWrite(LEFT_MOTOR_PIN,HIGH);
digitalWrite(RIGHT_MOTOR_PIN,HIGH);
Serial.println("Calibration Detected");
delay(9000); // a wait so you can back away from the robot while it is calibrating
digitalWrite(LEFT_MOTOR_PIN,HIGH);
digitalWrite(RIGHT_MOTOR_PIN,HIGH);
}
}

void loop(){
digitalWrite(ANT_WAVEFORM_OUT, HIGH);  //output antenna switching waveform
delay(1);
digitalWrite(ANT_WAVEFORM_OUT, LOW);
delay(1);
digitalWrite(ANT_WAVEFORM_OUT, HIGH);
delay(1);
digitalWrite(ANT_WAVEFORM_OUT, LOW);
delay(1);
digitalWrite(ANT_WAVEFORM_OUT, HIGH);
delay(1);
digitalWrite(ANT_WAVEFORM_OUT, LOW);
delay(1);
digitalWrite(ANT_WAVEFORM_OUT, HIGH);
delay(1);
digitalWrite(ANT_WAVEFORM_OUT, LOW);
delay(1);
voltage = analogRead(SPEAKER_FROM_WALKIETALKIE); //read voltage from radio
if (digitalRead(CALIBRATE_IN) == LOW){           //if in calibrate mode, store voltage in EEPROM
caliset = voltage;
byte HByte = highByte(caliset);
byte LByte = lowByte(caliset);
EEPROM.write(1, HByte);
EEPROM.write(2, LByte);
delay(5000);
endprogram();
}

if (voltage > (caliset - buffering) && voltage < (caliset + buffering)) { //drive forward

//motor control code for FORWARD here
//code for a continuous roating servo is included below
digitalWrite(LEFT_MOTOR_PIN,LOW);
digitalWrite(RIGHT_MOTOR_PIN,LOW);

}


if (voltage > (caliset + buffering)){ //turn

//motor control code for TURNING here (right or left depends on antenna config.)
//code for a continuous roating servo is included below
digitalWrite(LEFT_MOTOR_PIN,HIGH);
digitalWrite(RIGHT_MOTOR_PIN,LOW);
}
if (voltage < (caliset - buffering)){  //turn the other way

//motor control code for TURNING the OTHER DIRECTION here (right or left depends on antenna config.)
//code for a continuous roating servo is included below
digitalWrite(LEFT_MOTOR_PIN,LOW);
digitalWrite(RIGHT_MOTOR_PIN,HIGH);
}
delay(5); //just a simple wait
Serial.print("In, Cal\t");
Serial.print(voltage);
Serial.print("\t");
Serial.println(caliset);
}

void endprogram(){
  Serial.print("Calibrated to: ");
Serial.print(caliset);
  loopy:
  goto loopy;
}

