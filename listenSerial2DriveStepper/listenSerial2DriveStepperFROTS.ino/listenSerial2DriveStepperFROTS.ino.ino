#include <Arduino_FreeRTOS.h>
#include "L298P_Stepper.h"

// 定义步进电机每转的步数
const int stepsPerRevolution = 200;

// 创建步进电机对象
L298P_Stepper myStepper(9, 8, 12, 13, 3, 11); 

// 任务句柄
TaskHandle_t xHandleSerialListener = NULL;
TaskHandle_t xHandleStepperDriver = NULL;

// 标志位，用于指示是否收到串口信息
volatile bool messageReceived = false;

// 串口监听任务
void vTaskSerialListener(void *pvParameters) {
    for (;;) {
        if (Serial.available() > 0) {
            // 读取串口信息
            String incomingMessage = Serial.readStringUntil('\n');
            // 打印接收到的信息
            Serial.print("Received: ");
            Serial.println(incomingMessage);
            // 设置标志位，表示收到信息
            messageReceived = true;
        }
        vTaskDelay(pdMS_TO_TICKS(10));  // 延时 10 毫秒
    }
}

// 步进电机驱动任务
void vTaskStepperDriver(void *pvParameters) {
    for (;;) {
        if (messageReceived) {
            // 计算旋转 45 度所需的步数
            int steps = stepsPerRevolution * (45.0 / 360.0);
            // 驱动步进电机旋转
            myStepper.step(steps);
            // 打印步进电机旋转信息
            Serial.println("Stepper motor rotated 45 degrees.");
            // 停止步进电机
            myStepper.stop();
            // 重置标志位
            messageReceived = false;
        }
        vTaskDelay(pdMS_TO_TICKS(10));  // 延时 10 毫秒
    }
}

void setup() {
    // 初始化串口通信
    Serial.begin(9600);

    // 设置步进电机速度
    myStepper.setSpeed(30);

    // 创建任务
    xTaskCreate(
        vTaskSerialListener,   // 任务函数
        "SerialListener",      // 任务名称
        128,                   // 任务栈大小
        NULL,                  // 传递给任务函数的参数
        1,                     // 任务优先级
        &xHandleSerialListener // 任务句柄
    );

    xTaskCreate(
        vTaskStepperDriver,   // 任务函数
        "StepperDriver",      // 任务名称
        128,                  // 任务栈大小
        NULL,                 // 传递给任务函数的参数
        1,                    // 任务优先级
        &xHandleStepperDriver // 任务句柄
    );
}

void loop() {
    // 主循环中不需要做任何事情，任务由 FreeRTOS 调度
}