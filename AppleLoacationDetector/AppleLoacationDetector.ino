
int sensorValue ;
int lastSensorValue;  
int photoSensorPin = 7;
int ledPin = 12;
int intanPin =2;
void setup() {
  // 初始化串口通信
  Serial.begin(9600);

  // 设置LED引脚为输出模式
  pinMode(ledPin, OUTPUT);
  
  // establish the omron reader pins
   pinMode(photoSensorPin, INPUT_PULLUP);  
  
  // 初始化上一次的传感器状态  
  lastSensorValue = digitalRead(photoSensorPin);    //read the omron sensor
}

void loop() {
  digitalWrite(ledPin, LOW);
  // put your main code here, to run repeatedly:
  sensorValue  = digitalRead(photoSensorPin);
  Serial.println(sensorValue);
  // 判断传感器值是否大于零
  if (sensorValue==LOW && lastSensorValue == HIGH) {
    // 如果大于零，点亮LED
    digitalWrite(ledPin, HIGH);
    delay(5000);
    digitalWrite(ledPin, LOW);
    digitalWrite(intanPin, HIGH);
  } else {
    // 否则，关闭LED
    digitalWrite(ledPin, LOW);
  }
 // 更新上一次的传感器状态  
  lastSensorValue = sensorValue;  
  // 延迟一段时间，避免频繁读取
  delay(100);
}
