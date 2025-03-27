// 定义步进电机类
class L298P_Stepper {
public:
    L298P_Stepper(int ena, int enb, int in1, int in2, int pwmA, int pwmB);
    void setSpeed(long rpm);
    void stop();
    void step(int steps);

private:
    int _ena, _enb, _in1, _in2, _pwmA, _pwmB;
    int _currentPhase;
    int _direction;
    long _stepDelay;
    void _singleStep();
};

// 步进电机类的构造函数实现
L298P_Stepper::L298P_Stepper(int ena, int enb, int in1, int in2, int pwmA, int pwmB)
  : _ena(ena), _enb(enb), _in1(in1), _in2(in2), _pwmA(pwmA), _pwmB(pwmB) {
  
  // 初始化引脚模式
  pinMode(_ena, OUTPUT);
  pinMode(_enb, OUTPUT);
  pinMode(_in1, OUTPUT);
  pinMode(_in2, OUTPUT);
  pinMode(_pwmA, OUTPUT);
  pinMode(_pwmB, OUTPUT);

  // 初始状态：禁用所有输出
  digitalWrite(_ena, HIGH);
  digitalWrite(_enb, HIGH);
  _currentPhase = 0;
  _direction = 1;
}

// 设置步进电机速度的函数实现
void L298P_Stepper::setSpeed(long rpm) {
  // RPM转换为步间延迟（假设200步/转）
  if (rpm > 0) {
    _stepDelay = 60L * 1000L * 1000L / 200 / rpm; // 微秒延迟
  }
}

// 停止步进电机的函数实现
void L298P_Stepper::stop() {
      digitalWrite(_ena, HIGH);  //_ena=9  enb=8
      digitalWrite(_enb, HIGH);
      analogWrite(_pwmB, LOW); //in1=12
      analogWrite(_pwmA, LOW);
}

// 步进电机步进指定步数的函数实现
void L298P_Stepper::step(int steps) {
  // 确定旋转方向
  _direction = (steps >= 0) ? 1 : -1;
  steps = abs(steps);

  // 执行指定步数
  for (int i = 0; i < steps; i++) {
    _singleStep();
    delayMicroseconds(_stepDelay);
  }
}

// 步进电机单步操作的函数实现
void L298P_Stepper::_singleStep() {
  // 四相步进序列
  switch (_currentPhase) {
    case 0:  // 相位 0：通道A正转
      digitalWrite(_ena, LOW);  //_ena=9  enb=8
      digitalWrite(_enb, HIGH);
      digitalWrite(_in1, HIGH); //in1=12
      analogWrite(_pwmA, 255);
      
      break;

    case 1:  // 相位 3：通道B反转
      digitalWrite(_ena, HIGH);
      digitalWrite(_enb, LOW);
      digitalWrite(_in2, LOW);
      analogWrite(_pwmB, 255);
      
      break;

    case 2:  // 相位 2：通道A反转
      digitalWrite(_ena, LOW);
      digitalWrite(_enb, HIGH);
      digitalWrite(_in1, LOW);
      analogWrite(_pwmA, 255);
      
      break;
      
      case 3:  // 相位 1：通道B正转
      digitalWrite(_ena, HIGH);
      digitalWrite(_enb, LOW); 
      digitalWrite(_in2, HIGH); //in2=13
      analogWrite(_pwmB, 255);
      
      break;
  }

  // 更新相位（支持正反转）
  _currentPhase = (_currentPhase + _direction + 4) % 4;
}

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

// 初始化设置函数
void setup() {
  // 初始化串口通信
  Serial.begin(9600);
  // 设置步进电机的速度
  myStepper.setSpeed(30);
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
    myStepper.stop();
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
    myStepper.step(1);
    remainingSteps--;
    if (remainingSteps == 0) {
      isStepperMoving = false;
      myStepper.stop();
      Serial.println("Stepper motor rotated 45 degrees.");
    }
  }
}
    
