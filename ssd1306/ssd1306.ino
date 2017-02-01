#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  //display.display();
  //delay(2000);

  // Clear the buffer.
  display.clearDisplay();

  // draw scrolling text
  testscrolltext();

}

void loop() {
  
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
//  for (int i = 5; i < 121; i++) {
//    display.drawPixel(i, random(35, 41), WHITE);
//    display.display();
//    delay(100);
//  }
//  display.drawPixel(30, 50, WHITE);
//  display.drawPixel(40, 40, WHITE);
//  display.drawPixel(45, 20, WHITE);
//  display.display();
}
