#include "display.h"

namespace _DISPLAY {

  TFT_eSPI tft = TFT_eSPI();  // Invoke custom library
  uint16_t colors[] = { TFT_RED, TFT_GREEN, TFT_BLUE, TFT_CYAN, TFT_MAGENTA, TFT_YELLOW, TFT_WHITE, TFT_ORANGE, TFT_DARKGREY };

  /**
 * Colors are defined by 16-bit values representing RGB565 (5 bits red, 6 bits green, 5 bits blue)
 * This sets a maximum for each channel of 31, 63, and 31 respectively
 * */
  inline uint16_t getColor(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 11) | (g << 5) | b;
  }

  void begin(void) {
    tft.begin();
    tft.fillScreen(0);
    showSplashScreen();
  }

  void showSplashScreen() {
    tft.fillScreen(0);
    tft.drawRect(0, 0, tft.width(), tft.height(), TFT_MAGENTA);
    tft.setTextColor(TFT_WHITE);

    tft.setCursor(20, 60);
    tft.setTextFont(3);
    tft.print("Garhul's \n");
    tft.println("  CNC-Pendant");

    tft.setTextFont(2);
    tft.setTextColor(TFT_YELLOW);
    tft.setCursor(10, 216);
    tft.print("V 0.0.1");
    tft.setTextColor(TFT_CYAN);
    tft.setCursor(116, 216);
    tft.print("(c) Garhul's 2024");
    delay(1000);
    tft.fillScreen(TFT_BLACK);
  }

  void drawStatusBox(uint8_t status) {
    tft.fillRect(0, 0, 120, 40, 0);
    tft.setTextFont(4);
    tft.setCursor(4, 4);

    switch (status) {
    case ALARM:
      tft.drawRect(0, 0, 92, 31, TFT_RED);
      tft.setTextColor(TFT_RED, 0);
      tft.print("ALARM");
      break;
    case HOLD:
      tft.drawRect(0, 0, 80, 31, TFT_YELLOW);
      tft.setTextColor(TFT_YELLOW, 0);
      tft.print("HOLD");
      break;
    case IDLE:
      tft.drawRect(0, 0, 60, 31, getColor(0, 0b1111111, 0b11111));
      tft.setTextColor(getColor(0, 0b1111111, 0b11111), 0);
      tft.print("IDLE");
      break;
    case RUN:
      tft.drawRect(0, 0, 60, 31, TFT_GREEN);
      tft.setTextColor(TFT_GREEN, 0);
      tft.print("RUN");
      break;
    default:
      tft.setTextColor(TFT_WHITE);
      tft.print("???");
      break;
    }
  }

  void drawCoordSystemBox(char* text) {
    tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
    tft.setTextPadding(4);
    tft.setTextFont(3);
    tft.setCursor(180, 4);
    tft.print(text);
  }

  void printAxis(uint8_t startY, float value, uint16_t color, String label) {
    tft.setTextFont(4);
    tft.setCursor(2, startY);
    tft.setTextColor(color, 0);
    tft.print(label);

    tft.setCursor(48, startY);
    tft.setTextFont(7);
    tft.printf("%06.2f", value);
  }

  void test(void) {
    // tft->fillScreen(ST7735_BLACK);
    static float posX = 0;
    static float posY = 0;
    static float posZ = 0;



    // for (uint8_t i = 0; i < 9; i++) {
    //   tft.setTextFont(i);
    //   tft.setCursor(0, i * 20);
    //   tft.setTextColor(colors[i], 0);
    //   tft.printf("Font %d\n", i);
    //   delay(500);
    // }

    // drawStatusBox(0);
    // delay(1000);
    // drawStatusBox(1);
    // delay(1000);
    drawStatusBox(2);
    // delay(1000);
    // drawStatusBox(3);
    // delay(1000);
    // drawStatusBox(4);

    drawCoordSystemBox("G54");
    printAxis(40, posX, getColor(0b111111, 0b1111111, 0b11111), "X");
    printAxis(100, posY, TFT_MAGENTA, "Y");
    printAxis(160, posZ, TFT_GREENYELLOW, "Z");

    tft.setTextFont(4);
    tft.setCursor(0, 220);
    tft.setTextColor(getColor(15, 31, 15));
    tft.printf("Multi: %d      Feed: %d \%", 10, 120);

    // printf("took %d us\n", micros() - m);
    posX += .2;
    posY += .45;
    posZ += .3;

    delay(200);  // 1 second
  }

  // }  // namespace __DISPLAY

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
}  // namespace __DISPLAY