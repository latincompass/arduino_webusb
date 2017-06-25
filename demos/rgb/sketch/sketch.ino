
#include <FastLED.h>

#include <WebUSB.h>

#define NUM_LEDS 6
#define DATA_PIN 2
CRGB leds[NUM_LEDS];

const WebUSBURL URLS[] = {
  { 1, "webusb.github.io/arduino/demos/" },
  { 0, "localhost:8000" },
};

const uint8_t ALLOWED_ORIGINS[] = { 1, 2 };

WebUSB WebUSBSerial(URLS, 2, 1, ALLOWED_ORIGINS, 2);

#define Serial WebUSBSerial

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
int color[3];
int index;

void setup() {
  delay(2000);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  while (!Serial) {
    ;
  }
  Serial.begin(9600);
  Serial.write("Sketch begins.\r\n");
  Serial.flush();
  index = 0;
}

void loop() {
  if (Serial && Serial.available()) {
    color[index++] = Serial.read();
    if (index == 3) {
       leds[0] = CRGB(color[0],color[1],color[2]); 
       leds[1] = CRGB(color[0],color[1],color[2]); 
       leds[2] = CRGB(color[0],color[1],color[2]); 
       leds[3] = CRGB(color[0],color[1],color[2]); 
       leds[4] = CRGB(color[0],color[1],color[2]); 
       leds[5] = CRGB(color[0],color[1],color[2]); 
       FastLED.show();
      analogWrite(redPin, color[0]);
      analogWrite(greenPin, color[1]);
      analogWrite(bluePin, color[2]);
      Serial.print("Set LED to ");
      Serial.print(color[0]);
      Serial.print(", ");
      Serial.print(color[1]);
      Serial.print(", ");
      Serial.print(color[2]);
      Serial.print(".\r\n");
      Serial.flush();
      index = 0;
    }
  }
}
