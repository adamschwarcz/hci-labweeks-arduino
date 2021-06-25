/* FORCE SENSOR & LED STRIP CONTROL
 *  
 * Inspired by two tutorials:
 * LED Strip –> https://www.youtube.com/watch?v=EvRxQbhDxCo&t=11s
 * Force Sensor -> https://www.youtube.com/watch?v=JZ44h-jy0p4&t=94s
 * 
 * GitHub Repo:
 * https://github.com/adamschwarcz/hci-labweeks-arduino
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);
 
int sensorPin = 0; 
int sensorValue;
 
void setup(void) {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  
  strip.begin();
  strip.setBrightness(50);
  strip.show();
  Serial.begin(9600);
}
 
void loop(void) {
  sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue, 0, 1023, 0, 255);
  Serial.println(sensorValue);
  rainbow(20);
}

// LED Strip Rainbow Effect
void rainbow(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      sensorValue = analogRead(sensorPin);
      sensorValue = map(sensorValue, 0, 1023, 0, 255);
      Serial.println(sensorValue);
      if (sensorValue < 5) {
        strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        strip.show();
      } else {
      }
      delay(wait);
    }
  }
}

// LED Strip Wheel Transition
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
