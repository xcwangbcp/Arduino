/*************************************************************
  adapted from Randy Sarafan by xiaochun from the following refs,and added bt&omron sensor
  Motor Shield Stepper Demo

  Using the omron403N to stop the motor by digital read the his output which is about 4.2v

  by wang xiaochun

  For more information see:
  <a href="https://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/">
  https://www.instructables.com/id/Arduino-Motor-Sh...</a>

*************************************************************/

int delaylegnth = 20;
int bufferInt   = -1;
int nbstep      =  7;
int sensorVal   =  1;
unsigned long previousMillis = 0;

void setup() {

  //establish motor direction toggle pins
  pinMode(12, OUTPUT); //CH A -- HIGH = forwards and LOW = backwards
  pinMode(13, OUTPUT); //CH B -- HIGH = forwards and LOW = backwards

  //establish motor brake pins
  pinMode(9, OUTPUT); //brake (disable) CH A
  pinMode(8, OUTPUT); //brake (disable) CH B

  // establish the omron reader pins
  pinMode(7, INPUT); //read the omron sensor

  // Configure bluetooth connection rate
  Serial.begin(9600);
}

void loop() {
  sensorVal = 1;
  if (Serial.available() > 0) {         // Check for input
    bufferInt = Serial.read();
    if (bufferInt == '1') {

      for (int i = 0; i < nbstep + 1;  i++) {
        digitalWrite(9, LOW);  //ENABLE CH A
        digitalWrite(8, HIGH); //DISABLE CH B
        digitalWrite(12, HIGH);//Sets direction of CH A
        analogWrite(3, 255);   //Moves CH A
        //Serial.println("A");
        checkSensor;

        //moveMotorB;
        digitalWrite(9, HIGH);  //DISABLE CH A
        digitalWrite(8, LOW);   //ENABLE CH B
        digitalWrite(13, LOW);  //Sets direction of CH B
        analogWrite(11, 255);   //Moves CH B
        //Serial.println("B");
        checkSensor;

        //moveMotorAM;
        digitalWrite(9, LOW);  //ENABLE CH A
        digitalWrite(8, HIGH); //DISABLE CH B
        digitalWrite(12, LOW); //Sets direction of CH A
        analogWrite(3, 255);   //Moves CH A
        //Serial.println("A-");
        checkSensor;

        //moveMotorBM;
        digitalWrite(9, HIGH);  //DISABLE CH A
        digitalWrite(8, LOW);   //ENABLE CH B
        digitalWrite(13, HIGH); //Sets direction of CH B
        analogWrite(11, 255);   //Moves CH B
        //Serial.println("B-");
        checkSensor;

        if (i == nbstep) {
          stopStepper;
        }

      }// end for
    }// end BT if
  }// end loop
}

void stopStepper() {
  digitalWrite(9, HIGH);  //DISABLE CH A
  analogWrite(3, 0);      //stop Move CH A
  digitalWrite(8, HIGH);  //DISABLE CH B
  analogWrite(11, 0);     //stop Move CH B
  //Serial.println("stop");
  delay(delaylegnth);
}

void checkSensor() {
  while (sensorVal == 1) {
    unsigned long currentMillis = millis();
    sensorVal = digitalRead(7);
    if (sensorVal == 0) {
      stopStepper;
      break;
    }
    if (currentMillis - previousMillis >= delaylegnth) {
      previousMillis = currentMillis;
      break;
    }
  }
}
