//int  sensorVal=5;
void setup() {
  // put your setup code here, to run once:
  // establish the omron reader pins
  pinMode(7, INPUT_PULLUP); //read the omron sensor
  // Configure bluetooth connection rate
  //digitalWrite(7, HIGH);  
  //delay(0.2);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
//digitalWrite(7, HIGH);  
//delay(0.2);
int sensorVal = digitalRead(7);
delay(0.2);
Serial.println(sensorVal);
}
