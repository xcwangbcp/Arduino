/*************************************************************
Motor Shield Stepper Demo
by Randy Sarafan

For more information see:
<a href="https://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/">
https://www.instructables.com/id/Arduino-Motor-Sh...</a>

*************************************************************/

int delaylegnth = 30;
int bufferInt = -1;
int nbstep = 8;//2022-3-2经测试，可以控制motor的转动为25圈（？）
  
void setup() {
  
  //establish motor direction toggle pins
  pinMode(12, OUTPUT); //CH A -- HIGH = forwards and LOW = backwards
  pinMode(13, OUTPUT); //CH B -- HIGH = forwards and LOW = backwards
  
  //establish motor brake pins
  pinMode(9, OUTPUT); //brake (disable) CH A
  pinMode(8, OUTPUT); //brake (disable) CH B
  
 // Configure bluetooth connection rate
  Serial.begin(9600); 
}
 
  
void loop(){
  // Check for input
if (Serial.available() > 0) {
    bufferInt = Serial.read();
    Serial.println("Serial.read");
    Serial.println(bufferInt);
    switch (bufferInt){
  case '1':
  for(int i=0; i<nbstep; i++){
  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  digitalWrite(12, HIGH);   //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A
  
  delay(delaylegnth);
  
  digitalWrite(9, HIGH);  //DISABLE CH A
  digitalWrite(8, LOW); //ENABLE CH B
  digitalWrite(13, LOW);   //Sets direction of CH B
  analogWrite(11, 255);   //Moves CH B
  
  delay(delaylegnth);
  
  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  digitalWrite(12, LOW);   //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A
  
  delay(delaylegnth);
    
  digitalWrite(9, HIGH);  //DISABLE CH A
  digitalWrite(8, LOW); //ENABLE CH B
  digitalWrite(13, HIGH);   //Sets direction of CH B
  analogWrite(11, 255);   //Moves CH B
  
  delay(delaylegnth);
  //Serial.println("motor step");
  //Serial.println(i);
     }
  digitalWrite(9, HIGH);  //DISABLE CH A
  analogWrite(3, 0);   //stop Move CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  analogWrite(11, 0);   //stop Move CH B 
 break;
 case '2':
 bufferInt = Serial.read();
    Serial.println("Serial.read");
    Serial.println(bufferInt);
    break;
}
}
}
