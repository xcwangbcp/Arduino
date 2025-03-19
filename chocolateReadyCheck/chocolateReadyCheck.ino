// 定义开关连接的引脚
const int switchPin = 2;
int ledPin = 12;
// 用于存储开关状态的变量
int switchState = 0;

void setup() {
  // 初始化串口通信，用于输出开关状态
  Serial.begin(9600);
  
  // 将开关引脚设置为输入模式，并启用内部上拉电阻
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, LOW);
  // 读取开关引脚的状态
  switchState = digitalRead(switchPin);
  
  // 检查开关状态
  if (switchState == LOW) {
    // 开关被按下
    Serial.println("Switch is pressed!");
    digitalWrite(ledPin, HIGH);
    delay(100);
  } else {
    // 开关未被按下
    Serial.println("Switch is released!");
  }
  
  // 短暂延迟，避免频繁读取
  delay(100);
}
