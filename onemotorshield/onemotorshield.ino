//Parameters
const int input_voltage  = 12;//V
const int nominal_voltage  = 9;////V
const int MAX_SPEED  = int(nominal_voltage * 255 / input_voltage);
const int directionA  = 12;
const int brakeA  = 9;
const int speedA  = 3;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Serial.println(F("Initialize System"));
 //Init Motor Shield
 pinMode(directionA, OUTPUT); //Initiates Motor Channel A pin
 pinMode(brakeA, OUTPUT); //Initiates Brake Channel A pin
}
void testMotorMS() { /* function testMotorMS */
 //// Test DC motor
 Serial.println(F("-------------------------------------"));
 Serial.println(F("Avant "));
 dcForward();
 delay(500);
 Serial.println(F("Arrière "));
 dcBackward();
 delay(500);
 Serial.println(F("Arrêt "));
 dcStop();
 delay(1000);
}
void dcForward() { /* function dcForward */
 //// set forward motion for A and B
 digitalWrite(directionA, HIGH); //Establishes forward direction of Channel A
 digitalWrite(brakeA, LOW);   //Disengage the Brake for Channel A
 analogWrite(speedA, MAX_SPEED);
}
void dcBackward() { /* function dcBackward */
 //// set backward motion for A and B
 digitalWrite(directionA, LOW); //Establishes forward direction of Channel A
 digitalWrite(brakeA, LOW);   //Disengage the Brake for Channel A
 analogWrite(speedA, MAX_SPEED);
}
void dcStop() { /* function dcStop */
 //// stop motors A and B
 digitalWrite(brakeA, HIGH);   //Engage the Brake for Channel A
 analogWrite(speedA, 0);
}
void loop() {
  // put your main code here, to run repeatedly:

}
