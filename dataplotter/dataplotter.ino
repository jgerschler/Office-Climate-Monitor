#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4

Adafruit_SSD1306 display(OLED_RESET);

void setup()   {                
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64 Chinese knockoff)

  display.clearDisplay();

  testscrolltext();

}

void loop() {
  
}

void data_plot() {
  if (value > max_value) {
    max_value = value;
  }
  else if (value < min_value) {
    min_value = value;
  }
}

void init_plot() {
  
}

void testscrolltext(void) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.clearDisplay();
  display.println("Temp:");
  display.display();
  delay(2000);
  display.setCursor(0,0);
  display.clearDisplay();
  display.println("Pressure:");
  display.drawLine(0, 19, 0, 60, WHITE);
  display.setTextSize(1);
  display.setCursor(3, 16);
  display.println("50%");
  display.setCursor(3, 57);
  display.println("50%");
  display.display();
}
