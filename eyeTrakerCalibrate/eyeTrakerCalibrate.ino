

//Turns an LED on for one second, then off for one second, repeatedly.


//  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink

int point1Pin1 = 2;
int point1Pin2 = 3;
int point1Pin3 = 4;
int point1Pin4 = 5;
int point1Pin5 = 6;
int point1Pin6 = 7;
int point1Pin7 = 8;
int point1Pin8 = 9;
int point1Pin9 = 10;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(point1Pin1, OUTPUT);
  pinMode(point1Pin2, OUTPUT);
  pinMode(point1Pin3, OUTPUT);
  pinMode(point1Pin4, OUTPUT);
  pinMode(point1Pin5, OUTPUT);
  pinMode(point1Pin6, OUTPUT);
  pinMode(point1Pin7, OUTPUT);
  pinMode(point1Pin8, OUTPUT);
  pinMode(point1Pin9, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  for (int i = 2; i <= 10; i++) {
    digitalWrite(i, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(500);                      // wait for a second
    digitalWrite(i, LOW);   // turn the LED off by making the voltage LOW
    delay(500);                      // wait for a second
  }

  // digitalWrite(point1Pin1, HIGH);  // turn the LED on (HIGH is the voltage level)
  // delay(500);                      // wait for a second
  // digitalWrite(point1Pin1, LOW);   // turn the LED off by making the voltage LOW
  // delay(500);                      // wait for a second

}