#include "L298P_Stepper.h"

// 定义步进电机的步数和引脚
const int stepsPerRevolution = 200;                          // 步进电机每转的步数
L298P_Stepper myStepper(9, 8, 12, 13, 3, 11);  // 官方版的motor shield 9, 8, 12, 13, 3, 11；     盗版或者新版9, 8, 12, 13, 10, 11

// 标志位，用于指示是否收到串口信息
bool messageReceived = false;

// 步进电机任务相关变量
bool isStepperMoving = false;
int remainingSteps = 0;

// 记录时间的变量
unsigned long previousMillis = 0;
const long interval = 10; // 检查间隔时间，单位为毫秒

void setup() {
  // 初始化串口通信
  Serial.begin(9600);
  // 设置步进电机的速度
  myStepper.setSpeed(30);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // 任务1：监听串口信息
    checkSerialInput();

    // 任务2：驱动步进电机
    driveStepperIfNeeded();
    myStepper.stop();
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

void driveStepperIfNeeded() {
  if (messageReceived && !isStepperMoving) {
    // 计算旋转45度所需的步数
    int steps = stepsPerRevolution * (45.0 / 360.0);
    remainingSteps = steps;
    isStepperMoving = true;
    messageReceived = false;  // 重置标志位
  }

  if (isStepperMoving && remainingSteps > 0) {
    myStepper.step(1);
    remainingSteps--;
    if (remainingSteps == 0) {
      isStepperMoving = false;
      myStepper.stop();
      Serial.println("Stepper motor rotated 45 degrees.");
    }
  }
}
