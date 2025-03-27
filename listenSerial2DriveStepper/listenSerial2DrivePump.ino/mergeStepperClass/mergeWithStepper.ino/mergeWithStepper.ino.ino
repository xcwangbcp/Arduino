// 定义步进电机的引脚
int ena = 9;
int enb = 8;
int in1 = 12;
int in2 = 13;
int pwmA = 3;
int pwmB = 11;

// 定义步进电机的步数和引脚
const int stepsPerRevolution = 200;                          // 步进电机每转的步数

// 步进电机相关变量
int currentPhase = 0;
int direction = 1;
long stepDelay;

// 初始化引脚模式
void setupPins() {
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);

  // 初始状态：禁用所有输出
  digitalWrite(ena, HIGH);
  digitalWrite(enb, HIGH);
  analogWrite(pwmB, LOW);
  analogWrite(pwmA, LOW);
}

// 设置步进电机速度的函数
void setSpeed(long rpm) {
  // RPM转换为步间延迟（假设200步/转）
  if (rpm > 0) {
    stepDelay = 60L * 1000L * 1000L / 200 / rpm; // 微秒延迟
  }
}

// 停止步进电机的函数
void stopStepper() {
  digitalWrite(ena, HIGH);  
  digitalWrite(enb, HIGH);
  analogWrite(pwmB, LOW); 
  analogWrite(pwmA, LOW);
}

// 步进电机步进指定步数的函数
void step(int steps) {
  // 确定旋转方向
  direction = (steps >= 0) ? 1 : -1;
  steps = abs(steps);

  // 执行指定步数
  for (int i = 0; i < steps; i++) {
    singleStep();
    delayMicroseconds(stepDelay);
  }
}

// 步进电机单步操作的函数
void singleStep() {
  // 四相步进序列
  switch (currentPhase) {
    case 0:  // 相位 0：通道A正转
      digitalWrite(ena, LOW);  
      digitalWrite(enb, HIGH);
      digitalWrite(in1, HIGH); 
      analogWrite(pwmA, 255);
      
      break;

    case 1:  // 相位 3：通道B反转
      digitalWrite(ena, HIGH);
      digitalWrite(enb, LOW);
      digitalWrite(in2, LOW);
      analogWrite(pwmB, 255);
      
      break;

    case 2:  // 相位 2：通道A反转
      digitalWrite(ena, LOW);
      digitalWrite(enb, HIGH);
      digitalWrite(in1, LOW);
      analogWrite(pwmA, 255);
      
      break;
      
      case 3:  // 相位 1：通道B正转
      digitalWrite(ena, HIGH);
      digitalWrite(enb, LOW); 
      digitalWrite(in2, HIGH); 
      analogWrite(pwmB, 255);
      
      break;
  }

  // 更新相位（支持正反转）
  currentPhase = (currentPhase + direction + 4) % 4;
}

// 标志位，用于指示是否收到串口信息
bool messageReceived = false;

// 步进电机任务相关变量
bool isStepperMoving = false;
int remainingSteps = 0;

// 记录时间的变量
unsigned long previousMillis = 0;
const long interval = 10; // 检查间隔时间，单位为毫秒

// 初始化设置函数
void setup() {
  // 初始化串口通信
  Serial.begin(9600);
  // 初始化引脚
  setupPins();
  // 设置步进电机的速度
  setSpeed(30);
}

// 主循环函数
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // 任务1：监听串口信息
    checkSerialInput();

    // 任务2：驱动步进电机
    driveStepperIfNeeded();
    stopStepper();
  }
}

// 检查串口输入的函数
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

// 根据条件驱动步进电机的函数
void driveStepperIfNeeded() {
  if (messageReceived && !isStepperMoving) {
    // 计算旋转45度所需的步数
    int steps = stepsPerRevolution * (45.0 / 360.0);
    remainingSteps = steps;
    isStepperMoving = true;
    messageReceived = false;  // 重置标志位
  }

  if (isStepperMoving && remainingSteps > 0) {
    step(1);
    remainingSteps--;
    if (remainingSteps == 0) {
      isStepperMoving = false;
      stopStepper();
      Serial.println("Stepper motor rotated 45 degrees.");
    }
  }
}
