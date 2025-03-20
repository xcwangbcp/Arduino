// L298P_Stepper.cpp
#include "L298P_Stepper.h"
// 9 8 12 13 3 11 
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

void L298P_Stepper::setSpeed(long rpm) {
  // RPM转换为步间延迟（假设200步/转）
  if (rpm > 0) {
    _stepDelay = 60L * 1000L * 1000L / 200 / rpm; // 微秒延迟
  }
}

void L298P_Stepper::stop() {
      digitalWrite(_ena, HIGH);  //_ena=9  enb=8
      digitalWrite(_enb, HIGH);
      analogWrite(_pwmB, LOW); //in1=12
      analogWrite(_pwmA, LOW);
}

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