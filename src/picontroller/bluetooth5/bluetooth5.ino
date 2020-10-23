#include <ServoTimer1.h>

//#include <Servo.h>
#include <SoftwareSerial.h>


SoftwareSerial ss(6, 7);
ServoTimer1 grip;
ServoTimer1 lift;
const int MotorPinA = 12; // for motor A
const int MotorSpeedPinA = 3; // for motor A
const int MotorBrakePinA = 9; // for motor A


const int MotorPinB = 13; // for motor B
const int MotorSpeedPinB = 11;// for motor B
const int MotorBrakePinB = 8;// for motor B

const int CW  = HIGH;
const int CCW = LOW;

int rightServoVal = 9;
int leftServoVal = 9;

boolean newData = false;
const byte numChars = 32;
char receivedChars[numChars];

int button1High = 0;
int button2High = 0;
int button3High = 0;
int button4High = 0;
float liftDeg = 150;
float gripDeg = 25;
float liftPos = 0;
float oldGripDeg = 25;
float oldLiftDeg = 150;

void setup() {
  Serial.begin( 9600 );//  baud rate 9600 for the serial Bluetooth communication
    // motor A pin assignment
  pinMode(MotorPinA, OUTPUT);
  pinMode(MotorSpeedPinA, OUTPUT);
  pinMode(MotorBrakePinA, OUTPUT);

  // motor B pin assignment
  pinMode(MotorPinB, OUTPUT);
  pinMode(MotorSpeedPinB, OUTPUT);
  pinMode(MotorBrakePinB, OUTPUT); 

  grip.attach(10);
  lift.attach(9);
  lift.write(150);
  
  ss.begin(9600);
}
void loop() {
  // listen for the data from raspberry pi

  getDataFromPC();
  if (newData == true) {
    newData = false;
    setMotor();
  }
  updateServoGripVal();
  updateServoLiftVal();
  if (oldLiftDeg != liftDeg) {
    oldLiftDeg = liftDeg;
    setLift(); 
  }
  if (oldGripDeg != gripDeg) {
   oldGripDeg = gripDeg;
   setGrip(); 
  }
  //Serial.println(button4High);
  
  

  

}

void getDataFromPC() {

    // receive data from PC and save it into inputBuffer

    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (ss.available() > 0 && newData == false) {
        rc = ss.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
                parseData();
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void parseData() {

    // split the data into its parts 
  char * strtokIndx; // this is used by strtok() as an index
  
  strtokIndx = strtok(receivedChars,","); // this continues where the previous call left off
  leftServoVal = atoi(strtokIndx);     // convert this part to an integer
  
  strtokIndx = strtok(NULL, ","); 
  rightServoVal = atoi(strtokIndx);     // convert this part to an integer
  
  strtokIndx = strtok(NULL, ","); 
  button1High = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ","); 
  button2High = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ","); 
  button3High = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ","); 
  button4High = atoi(strtokIndx);
  //Utvid her
}

void setMotor() {
  if (leftServoVal == 9) {
    analogWrite(MotorSpeedPinA, 0);
  } else if (leftServoVal > 9) {
    digitalWrite(MotorPinA, CW);
    analogWrite(MotorSpeedPinA, map(leftServoVal, 9, 18, 0, 255));
  } else {
    digitalWrite(MotorPinA, CCW);
    analogWrite(MotorSpeedPinA, map(leftServoVal, 9, 0, 0, 255));
  }

  if (rightServoVal == 9) {
    analogWrite(MotorSpeedPinB, 0);
  } else if (rightServoVal > 9) {
    digitalWrite(MotorPinB, CW);
    analogWrite(MotorSpeedPinB, map(rightServoVal, 9, 18, 0, 255));
  } else {
    digitalWrite(MotorPinB, CCW);
    analogWrite(MotorSpeedPinB, map(rightServoVal, 9, 0, 0, 255));
  }

}
//Inkrementell funksjon 
void updateServoLiftVal() {
  if (button4High) {
    if (liftDeg > 60) {
      liftDeg -= 0.005;
    }
  }
  if (button2High) {
    if(liftDeg < 160) {
      liftDeg += 0.005;
    }
  }
  
}
//Hjelpefunksjon til gradvis posisjon 
void setLift() {
  lift.write(liftDeg);
}
// Setter umiddelbar posisjon (Ikke i bruk)
void setLiftPos() {
  // Setter nedre posisjon
  if (button2High) {
    lift.write(150); 
  }
  // Setter øvre posisjon
  if (button4High) {
    lift.write(80);
  }
}
// Funksjon for jevn åpning/lukking
void updateServoGripVal() {
  // Åpne
  if (button3High) {
    if (gripDeg < 110) {
      gripDeg += 0.025;
    }
  }
  if (button1High) {
    if(gripDeg > 20) {
      gripDeg -= 0.025;
    }
  }
  
}

void setGrip() {
  grip.write(gripDeg);
}
