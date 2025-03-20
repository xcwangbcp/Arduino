// L298P_Stepper.h
#ifndef L298P_STEPPER_H
#define L298P_STEPPER_H

#include <Arduino.h>

class L298P_Stepper {
  public:
    // 构造函数（引脚初始化）
    L298P_Stepper(int ena, int enb, int in1, int in2, int pwmA, int pwmB);

    // 设置转速（RPM）
    void setSpeed(long rpm);

    // 步进控制（正数为顺时针，负数为逆时针）
    void step(int steps);
    // stop stepper
    void stop();

  private:
    // 引脚定义
    int _ena, _enb;    // 使能引脚（低电平有效）
    int _in1, _in2;    // 方向控制引脚
    int _pwmA, _pwmB;  // PWM速度引脚

    // 运行参数
    unsigned long _stepDelay;  // 步间延迟（微秒）
    int _currentPhase;        // 当前相位（0-3）
    int _direction;           // 旋转方向（1:正，-1:反）

    // 单步执行函数
    void _singleStep();
};

#endif