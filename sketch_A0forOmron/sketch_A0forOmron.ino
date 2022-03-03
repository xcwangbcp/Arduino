//just read out either a digital or a analog input and print it out
// work as a potentialometer,as the volts will change after connected to a 
//diffrent circuits.by xiaochun wang 

int analogPin = A0; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int digitalPin = 4;                   
int valA = 0;  // variable to store the value read
int valD = 0;
int nbstep =30;
int bufferInt = -1;
int delaylegnth = 500;
void setup() {
  Serial.begin(9600);           //  setup serial
  pinMode(digitalPin, INPUT); //read the omron sensor
  
}

void loop() {
  if (Serial.available() > 0) {
    bufferInt = Serial.read();
if (bufferInt == '1') {
  for(int i=0; i<nbstep; i++){
    valA = analogRead(analogPin);  // read the input pin
    valD =digitalRead(digitalPin);
    delay(delaylegnth);
    Serial.println(valA*5/1024);          // debug value
    Serial.println(valD );
}
}
}
}
