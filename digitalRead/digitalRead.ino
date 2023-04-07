int  sensorVal=5;
void setup() {
  // put your setup code here, to run once:
  // establish the omron reader pins
  pinMode(7, INPUT_PULLUP); //read the omron sensor
  // Configure bluetooth connection rate
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
//digitalWrite(7, HIGH);  
//delay(2);
sensorVal = digitalRead(7);
delay(2);
Serial.println(sensorVal);
}
