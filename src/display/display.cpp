#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <font.h>

// #define GFX_BL DF_GFX_BL  // default backlight pin, you may replace DF_GFX_BL to actual backlight pin

// /* More dev device declaration: https://github.com/moononournation/Arduino_GFX/wiki/Dev-Device-Declaration */
// #if defined(DISPLAY_DEV_KIT)

// #else /* !defined(DISPLAY_DEV_KIT) */

// /* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
// Arduino_DataBus *bus = create_default_Arduino_DataBus();

// /* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
// Arduino_GFX *gfx = new Arduino_ST7735(bus, DF_GFX_RST, 0 /*rotation*/, false /* ips */);
// //  new Arduino_ILI9341(bus, DF_GFX_RST, 0 /* rotation */, false /* IPS */);
// //

// #endif /* !defined(DISPLAY_DEV_KIT) */
// /*******************************************************************************
//  * End of Arduino_GFX setting
//  ******************************************************************************/

namespace __DISPLAY {
Arduino_GFX *gfx = create_default_Arduino_GFX();

void setup(void) {
  gfx->begin();
  gfx->fillScreen(BLACK);

#ifdef GFX_BL
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
#endif
}

void printAxis(uint8_t startY, uint16_t value, uint16_t color, String label) {
  gfx->setFont(&FreeMono9pt7b);
  gfx->setCursor(0, startY);
  gfx->setTextColor(color, 0);
  gfx->setTextSize(2, 2, 0);
  gfx->println(label);
  gfx->setTextSize(1, 1, 1);
  gfx->setCursor(32, startY);
  gfx->println(String(value, DEC) + String(".015"));
}

}  // namespace __DISPLAY

// void loop() {
//   uint16_t posX = random(0, 2000);
//   uint16_t posY = random(0, 2000);
//   uint16_t posZ = random(0, 2000);
//   printAxis(20, posX, GREEN, "X");
//   printAxis(60, posY, YELLOW, "Y");
//   printAxis(100, posZ, MAGENTA, "Z");
//   delay(400);  // 1 second
//   // put your main code here, to run repeatedly:
//   strip.SetPixelColor(0, RgbColor(random(0, 10), 0, random(0, 10)));
//   strip.Show();
// }