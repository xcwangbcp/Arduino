/// @file    DemoReel100.ino
/// @brief   FastLED "100 lines of code" demo reel, showing off some effects
/// @example DemoReel100.ino

#include <FastLED.h>

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014


#define DATA_PIN    3
//#define CLK_PIN   4
#define LED_TYPE    SK6812
#define COLOR_ORDER GRB
#define NUM_LEDS    30
CRGB leds[NUM_LEDS];

#define BRIGHTNESS     50
#define FRAMES_PER_SECOND  
const int speakerPin = 9;  // 定义扬声器连接的引脚  
void setup() {
  delay(100); // 300ms second delay for recovery
  Serial.begin(9600);  // 初始化串口，波特率为 9600  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(speakerPin, OUTPUT);  
}
 

void loop() {  
  if (Serial.available() > 0) { // 检查是否有串口数据  
    char incomingByte = Serial.read(); // 读取串口输入的数据  

    // 根据接收到的字符控制 LED  
    if (incomingByte == 'H') {  
       fill_solid(leds,NUM_LEDS,CRGB::White);
       tone(speakerPin, 40); // 播放40Hz的声音  
       FastLED.show();
       delay(1000);
    } else if (incomingByte == 'L') {  
      fill_solid(leds,NUM_LEDS,CRGB::Black);
      noTone(speakerPin); // 停止发声  
      FastLED.show();
      delay(1000); 
    }  
  }  
}
