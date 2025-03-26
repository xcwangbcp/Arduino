// 实现方便测试，目前code ，第一次按键，闪1秒，间隔2秒持续闪下去，第二次按键，闪5秒，再也不闪了。  想让他工作再，断电后再上电
// 定义按钮引脚
const int buttonPin = 2;
// 定义LED引脚
const int ledPin = 12;

// 存储按钮的上一次状态
int lastButtonState = HIGH;
// 存储当前按钮状态
int buttonState;
// 存储上次读取按钮的时间
unsigned long lastDebounceTime = 0;
// 消抖时间（毫秒）
unsigned long debounceDelay = 50;
// 存储上次LED闪烁开始的时间
unsigned long lastFlashStartTime = 0;
// 存储上次LED闪烁的时间
unsigned long lastFlashTime = 0;
// LED闪烁间隔时间（毫秒），这里设置为1分钟
unsigned long flashInterval = 2000;
// LED闪烁持续时间（毫秒）
unsigned long flashDuration = 1000;
// 标记LED是否需要闪烁
bool shouldFlash = false;
// 标记LED是否正在闪烁
bool isFlashing = false;
// 标记按钮按下次数
int buttonPressCount = 0;
// 第二次按下按钮后LED闪烁1秒的开始时间
unsigned long secondPressFlashStartTime = 0;
// 标记是否是第二次按下按钮触发的闪烁
bool isSecondPressFlash = false;

void setup() {
    // 将按钮引脚设置为输入模式
    pinMode(buttonPin, INPUT_PULLUP);
    // 将LED引脚设置为输出模式
    pinMode(ledPin, OUTPUT);
}

void loop() {
    // 读取按钮状态
    int reading = digitalRead(buttonPin);

    // 检查按钮状态是否改变
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    // 如果消抖时间已过
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
            buttonState = reading;

            // 如果按钮被按下（低电平）
            if (buttonState == LOW) {
                buttonPressCount++;
                if (buttonPressCount == 1) {
                    // 首次按下，触发LED闪100ms
                    shouldFlash = true;
                    lastFlashStartTime = millis();
                    isFlashing = true;
                    digitalWrite(ledPin, HIGH);
                } else if (buttonPressCount == 2) {
                    // 第二次按下，闪LED 1秒钟
                    shouldFlash = false;
                    isFlashing = false;
                    digitalWrite(ledPin, LOW);
                    secondPressFlashStartTime = millis();
                    isSecondPressFlash = true;
                } else {
                    // 再次按下，停止闪烁
                    shouldFlash = false;
                    isFlashing = false;
                    isSecondPressFlash = false;
                    digitalWrite(ledPin, LOW);
                    // 程序结束后可以在这里添加其他逻辑，例如进入低功耗模式等
                    while (true) {
                        // 程序结束，进入无限循环
                    }
                }
            }
        }
    }

    // 如果是第二次按下按钮触发的闪烁
    if (isSecondPressFlash) {
        if (millis() - secondPressFlashStartTime < 5000) {
            digitalWrite(ledPin, HIGH);
        } else {
            isSecondPressFlash = false;
            digitalWrite(ledPin, LOW);
        }
    }

    // 如果LED需要闪烁
    if (shouldFlash) {
        if (isFlashing) {
            // 检查闪烁是否结束
            if (millis() - lastFlashStartTime >= flashDuration) {
                digitalWrite(ledPin, LOW);
                isFlashing = false;
                lastFlashTime = millis();
            }
        } else {
            // 检查是否到了下一次闪烁时间
            if (millis() - lastFlashTime >= flashInterval) {
                lastFlashStartTime = millis();
                isFlashing = true;
                digitalWrite(ledPin, HIGH);
            }
        }
    }

    // 更新按钮的上一次状态
    lastButtonState = reading;
}
    