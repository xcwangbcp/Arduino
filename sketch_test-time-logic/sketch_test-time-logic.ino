/*************************************************************
adapted from Randy Sarafan by xiaochun from the following refs,and added bt&omron sensor 
Motor Shield Stepper Demo

Using the omron403N to stop the motor by digital read the his output which is about 4.2v

by wang xiaochun

For more information see:
<a href="https://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/">
https://www.instructables.com/id/Arduino-Motor-Sh...</a>

*************************************************************/

int delaylegnth = 100;
int bufferInt = -1;
int nbstep =2;
int sensorVal=1;

const long interval = 5;   

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
  
void loop(){
int sensorVal=1;
  // Check for input
if (Serial.available() > 0) {
    bufferInt = Serial.read();
    //Serial.println("Serial.read");Serial.println(bufferInt);
if (bufferInt == '1') {
  //Serial.println("channel7 out");
  //Serial.println(sensorVal);
for (int i=0;i<nbstep;i++){
  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  digitalWrite(12, HIGH);//Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A
  Serial.println("A");
  sensorVal = digitalRead(7);
  unsigned long currentMillis = millis();
  Serial.println(currentMillis);
  int dif = currentMillis - previousMillis;
  while(dif >= delaylegnth) {
    previousMillis = currentMillis;
    Serial.println(i);
    Serial.println("previousMillis");
    Serial.println(previousMillis);
    if 
  //Serial.println("channel 7");
  //Serial.println(sensorVal);
  if (sensorVal==LOW) {
  digitalWrite(9, HIGH);  //DISABLE CH A
  analogWrite(3, 0);      //stop Move CH A
  digitalWrite(8, HIGH);  //DISABLE CH B
  analogWrite(11, 0);     //stop Move CH B
  delay(delaylegnth);
  Serial.println("break");
  break;
  } 
  }

 
 digitalWrite(9, HIGH);  //DISABLE CH A
 digitalWrite(8, LOW);   //ENABLE CH B
 digitalWrite(13, LOW);  //Sets direction of CH B
 analogWrite(11, 255);   //Moves CH B
 Serial.println("B-");
 sensorVal =digitalRead(7);
 //Serial.println("channel 7");
 //Serial.println(sensorVal);
 currentMillis = millis();
 Serial.println(currentMillis);
 if (currentMillis - previousMillis >= delaylegnth) {
    previousMillis = currentMillis;
   Serial.println(i);
   Serial.println("previousMillis");
   Serial.println(previousMillis);
   
  if (sensorVal==LOW) {
  digitalWrite(9, HIGH);  //DISABLE CH A
  analogWrite(3, 0);      //stop Move CH A
  digitalWrite(8, HIGH);  //DISABLE CH B
  analogWrite(11, 0);    //stop Move CH B
  delay(delaylegnth);
  Serial.println("break");
  break;
  } 
  }

  
  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  digitalWrite(12, LOW); //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A
  Serial.println("A-");
  //sensorVal =digitalRead(7);
  //Serial.println("channel 7");
  //Serial.println(sensorVal);
  currentMillis = millis();
 Serial.println(currentMillis);
  if (currentMillis - previousMillis >= delaylegnth) {
  previousMillis = currentMillis;
  Serial.println("previousMillis");
  Serial.println(previousMillis);
 
  if (sensorVal==LOW) {
  digitalWrite(9, HIGH);  //DISABLE CH A
  analogWrite(3, 0);      //stop Move CH A
  digitalWrite(8, HIGH);  //DISABLE CH B
  analogWrite(11, 0);     //stop Move CH B
  delay(delaylegnth);
  Serial.println("break");
  break;
  } 
  }
  
 
  digitalWrite(9, HIGH);  //DISABLE CH A
  digitalWrite(8, LOW);   //ENABLE CH B
  digitalWrite(13, HIGH); //Sets direction of CH B
  analogWrite(11, 255);   //Moves CH B
  Serial.println("B");
  sensorVal =digitalRead(7);
  //Serial.println("channel 7");
  //Serial.println(sensorVal);
  currentMillis = millis();
  Serial.println(currentMillis);
  if (currentMillis - previousMillis >= delaylegnth) {
  previousMillis = currentMillis;
  Serial.println("previousMillis");
  Serial.println(previousMillis);

  if (sensorVal==LOW) {
  digitalWrite(9, HIGH);  //DISABLE CH A
  analogWrite(3, 0);      //stop Move CH A
  digitalWrite(8, HIGH);  //DISABLE CH B
  analogWrite(11, 0);     //stop Move CH B
  delay(delaylegnth);
  Serial.println("break");
  break;
  } 
  }
  Serial.println(i);
}

  digitalWrite(9, HIGH);  //DISABLE CH A
  analogWrite(3, 0);      //stop Move CH A
  digitalWrite(8, HIGH);  //DISABLE CH B
  analogWrite(11, 0);     //stop Move CH B
  delay(delaylegnth);
  Serial.println("stop motor");
  }
}
}
