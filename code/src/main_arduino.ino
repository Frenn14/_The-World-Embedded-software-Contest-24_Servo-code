#include <Servo.h> //add Servo lib
#include <SoftwareSerial.h> // add bluetooth lib

#define SERVO  7   //Servo pin number
#define BT_RX  2   //Bluetooth Rx pin number
#define BT_TX  3   //Bluetooth Tx pin number

Servo servo; //Servo class, servo
SoftwareSerial bluetooth(BT_RX, BT_TX);

int valServoClose = 152; // close servo rotation value
int valServoOpen = 140; // open servo rotation value
int valServo = valServoClose; // servo rotation value, default is closed
char valBTdata;

void setup() {
  Serial.begin(9600); // Serial Set
  bluetooth.begin(9600); // BT Serial Set
}

void servoOpen() { // function 'servoOpen'
  valServo = valServoOpen; // Servo value change to Open value
}

void servoClose() { // function 'servoClose'
  valServo = valServoClose; // Servo value change to close value
}

void loop() {
  if(bluetooth.available()) { // if taking data to bluetooth
    valBTdata = bluetooth.available();

    if(valBTdata == 'o') { // if taking data is open sign
      servoOpen(); // servo opening
    } 
    else if(valBTdata == 'c') { // if taking data is close sign
      servoClose(); // servo closing
    }

    Serial.println(valBTdata); // print read data
  }
  if(Serial.available()) { // if taking data to Serial
    bluetooth.write(Serial.read()); // giving data to bluetooth
  }
  servo.write(valServo); // setting servo rotation
}
