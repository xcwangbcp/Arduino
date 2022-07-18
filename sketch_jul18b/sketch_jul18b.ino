int delaylegnth = 10;
int bufferInt = -1;


  
void setup() {
  
  //establish motor direction toggle pins
  pinMode(12, OUTPUT); //CH A -- HIGH = forwards and LOW = backwards
  pinMode(13, OUTPUT); //CH B -- HIGH = forwards and LOW = backwards
  
  //establish motor brake pins
  pinMode(9, OUTPUT); //brake (disable) CH A
  pinMode(8, OUTPUT); //brake (disable) CH B
  
  // establish the omron reader pins
  pinMode(4, INPUT); //read the omron sensor
  
 // Configure bluetooth connection rate
  Serial.begin(9600); 
}
 
  
void loop(){
int nbstep =50;
int sensorVal=1;
int i=0;
 
  // Check for input
if (Serial.available() > 0) {
    bufferInt = Serial.read();
if (bufferInt == '1') {
  sensorVal =digitalRead(4);
  
  while (sensorVal==HIGH) {
  sensorVal =digitalRead(4);
  Serial.println("channel4 out");
  Serial.println(sensorVal);
 
  i++;
  //for(int i=0; i<nbstep; i++){
   if (sensorVal==LOW) {
  digitalWrite(9, HIGH);  //DISABLE CH A
  analogWrite(3, 0);      //stop Move CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  analogWrite(11, 0);   //stop Move CH B
  delay(delaylegnth);
    break;
  }
  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  digitalWrite(12, HIGH);   //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A
  delay(delaylegnth);
sensorVal =digitalRead(4);
if (sensorVal==LOW) {
  digitalWrite(9, HIGH);  //DISABLE CH A
  analogWrite(3, 0);      //stop Move CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  analogWrite(11, 0);   //stop Move CH B
  delay(delaylegnth);
    break;
  }
  
  digitalWrite(9, HIGH);  //DISABLE CH A
  digitalWrite(8, LOW); //ENABLE CH B
  digitalWrite(13, LOW);   //Sets direction of CH B
  analogWrite(11, 255);   //Moves CH B
  delay(delaylegnth);

 sensorVal =digitalRead(4);
  if (sensorVal==LOW) {
  digitalWrite(9, HIGH);  //DISABLE CH A
  analogWrite(3, 0);      //stop Move CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  analogWrite(11, 0);   //stop Move CH B
  delay(delaylegnth);
    break;
  }
  
  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  digitalWrite(12, LOW);   //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A
  delay(delaylegnth);

   sensorVal =digitalRead(4);
   if (sensorVal==LOW) {
  digitalWrite(9, HIGH);  //DISABLE CH A
  analogWrite(3, 0);      //stop Move CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  analogWrite(11, 0);   //stop Move CH B
  delay(delaylegnth);
    break;
  }
  
  digitalWrite(9, HIGH);  //DISABLE CH A
  digitalWrite(8, LOW); //ENABLE CH B
  digitalWrite(13, HIGH);   //Sets direction of CH B
  analogWrite(11, 255);   //Moves CH B
  delay(delaylegnth);

  sensorVal =digitalRead(4);
  if (sensorVal==LOW) {
  digitalWrite(9, HIGH);  //DISABLE CH A
  analogWrite(3, 0);      //stop Move CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  analogWrite(11, 0);   //stop Move CH B
  delay(delaylegnth);
    break;
  }
  
  Serial.println("motor step" );
  Serial.println(i);

  if (i>10){
  digitalWrite(9, HIGH);  //DISABLE CH A
  analogWrite(3, 0);   //stop Move CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  analogWrite(11, 0);   //stop Move CH B
  delay(delaylegnth);
  break;
  }
  //
  //}
  }
//else{
  //Serial.println("channel4 out");
  //Serial.println(sensorVal);
  //digitalWrite(9, HIGH);  //DISABLE CH A
  //analogWrite(3, 0);   //stop Move CH A
  //digitalWrite(8, HIGH); //DISABLE CH B
  //analogWrite(11, 0);   //stop Move CH B
  //}
  
}
}
}
