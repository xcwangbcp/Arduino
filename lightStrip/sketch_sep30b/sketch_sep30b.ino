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

void setup() {
  delay(300); // 300ms second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}
void loop() { 
  // Turn the LED on, then pause
  //leds = CRGB::White;
  fill_solid(leds,NUM_LEDS,CRGB::White);
  FastLED.show();
  delay(500);
  // Now turn the LED off, then pause
  //leds= CRGB::Black;
  fill_solid(leds,NUM_LEDS,CRGB::Black);
  FastLED.show();
  delay(500);
}


