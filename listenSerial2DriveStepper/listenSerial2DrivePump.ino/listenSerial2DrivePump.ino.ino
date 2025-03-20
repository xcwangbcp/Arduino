#include <Arduino_FreeRTOS.h>

// 任务句柄
TaskHandle_t xHandleSerialListener = NULL;
TaskHandle_t xHandlePinControl = NULL;

// 标志位，用于指示是否收到串口信息
volatile bool messageReceived = false;
// 高电平持续时间（毫秒）
const int highLevelDuration = 200; 


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

// 引脚控制任务
void vTaskPinControl(void *pvParameters) {
    pinMode(2, OUTPUT);
    for (;;) {
        if (messageReceived) {
            digitalWrite(2, HIGH);
            vTaskDelay(pdMS_TO_TICKS(highLevelDuration));
            digitalWrite(2, LOW);
            // 重置标志位
            messageReceived = false;
        }
        vTaskDelay(pdMS_TO_TICKS(10));  // 延时 10 毫秒
    }
}

void setup() {
    // 初始化串口通信
    Serial.begin(9600);

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
        vTaskPinControl,   // 任务函数
        "PinControl",      // 任务名称
        128,               // 任务栈大小
        NULL,              // 传递给任务函数的参数
        1,                 // 任务优先级
        &xHandlePinControl // 任务句柄
    );
}

void loop() {
    // 主循环中不需要做任何事情，任务由 FreeRTOS 调度
}
