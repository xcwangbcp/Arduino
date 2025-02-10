const int speakerPin = 9;  // 定义扬声器连接的引脚  

void setup() {  
  // 初始化引脚为输出  
  pinMode(speakerPin, OUTPUT);  
}  

void loop() {  
  // 产生40Hz的声音  
 // for (int i = 0; i < 400; i++) { // 400个脉冲，约1秒  
      tone(speakerPin, 40); // 播放40Hz的声音  
      delay(1000); // 声音持续1秒  
      noTone(speakerPin); // 停止发声  
      delay(1000); // 每次循环后暂停1秒  

    //digitalWrite(speakerPin, HIGH); // 输出高电平  
    //delayMicroseconds(12500); // 高电平持续时间 (1 / (2 * 40Hz) * 1,000,000us)  
    //digitalWrite(speakerPin, LOW); // 输出低电平  
    //delayMicroseconds(12500); // 低电平持续时间  
  //}  

  delay(1000); // 每次循环后暂停1秒  
}