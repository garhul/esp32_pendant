#include <NeoPixelBus.h>

#include "./inputs/inputs.h"
#include "Arduino.h"
#define STRIP_LEN 16
#define REL 0.003921569f

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> leds(STRIP_LEN, 15);

void setup() {
  Serial.begin(115200);
  Serial.println("PRE coso");
  __INPUTS::begin();
  // leds.Begin();
  // leds.Show();
}

void loop() {
  Serial.println("Main loop");
  // static byte skew = 0;
  // byte i = 0;
  // for (i; i < STRIP_LEN; i++) {
  //   // Serial.println(i);
  //   // skew++;
  //   // delay(100);
  //   // leds.SetPixelColor(i, HsbColor((i + skew) * REL, 1, .04));
  // }

  // skew++;
  // leds.Show();

  __INPUTS::poll();
  delay(1000);
}
