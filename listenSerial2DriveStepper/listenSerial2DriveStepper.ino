#include <Stepper.h>

// 定义步进电机的步数和引脚
const int stepsPerRevolution = 200;  // 步进电机每转的步数
Stepper myStepper(stepsPerRevolution, 12, 13, 3, 11);// 官方版的motor shield

// 标志位，用于指示是否收到串口信息
bool messageReceived = false;

void setup() {
  // 初始化串口通信
  Serial.begin(9600);
  // 设置步进电机的速度
  myStepper.setSpeed(30);
}

void loop() {
  // 任务1：监听串口信息
  checkSerialInput();

  // 任务2：如果收到信息，驱动步进电机旋转45度
  if (messageReceived) {
    driveStepper();
    messageReceived = false;  // 重置标志位
  }
}

void checkSerialInput() {
  if (Serial.available() > 0) {
    // 读取串口信息
    String incomingMessage = Serial.readStringUntil('\n');
    // 打印接收到的信息
    Serial.print("Received: ");
    Serial.println(incomingMessage);
    // 设置标志位，表示收到信息
    messageReceived = true;
  }
}

void driveStepper() {
  // 计算旋转45度所需的步数
  int steps = stepsPerRevolution * (45.0 / 360.0);
  // 驱动步进电机旋转
  myStepper.step(steps);
  // 打印步进电机旋转信息
  Serial.println("Stepper motor rotated 45 degrees.");
}    