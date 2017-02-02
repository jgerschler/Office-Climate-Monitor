/*Things that need to be done:
Set up millis timers:
  1)Check every ten seconds if lights have been turned off.
    a)inside loop, check if analog voltage has changed past threshold.
      i)if yes, then turn on LCD backlight, and set pins high for ambient lighting.
      ii)if lights are already on, keep on, etc.
  1.5)Switch every ten seconds to secondary OLED display.
    a)plot data held in respective array.
  2)Check every minute for new environmental data.
    a)update array
    b)update LCD
  3)Plot every minute environmental data.
*/

//#include <SPI.h>//do we need this?
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h>

#define OLED_RESET 4

Adafruit_SSD1306 display(OLED_RESET);
LiquidCrystal_I2C LCD(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int temperature_array[121];
int pressure_array[121];
int min_y = 0;
int max_y = 0;
int min_val;
int max_val;
int value = 1;
unsigned long previousMillis = 0;

void setup()   {                
//  Serial.begin(9600);
  //get data here before updating displays
  LCD.begin(20, 4);
  LCD.clear();
  LCD.backlight();
  LCD.setCursor(0,0);
  LCD.print("Temp:");//add variables here
  LCD.setCursor(0,1);
  LCD.print("Humidity:");
  LCD.setCursor(0,2);
  LCD.print("Pressure:");
  LCD.setCursor(0,3);
  LCD.print("Altitude:");
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void update_lcd {
  LCD.clear();
  LCD.setCursor(0,0);
  LCD.print("Temp:");//add variables here
  LCD.setCursor(0,1);
  LCD.print("Humidity:");
  LCD.setCursor(0,2);
  LCD.print("Pressure:");
  LCD.setCursor(0,3);
  LCD.print("Altitude:");
}


void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 10000) {
    //things happening every ten seconds
    previousMillis = currentMillis;
  }
  if (currentMillis - previousMillis >= 60000) {
    //things happening every minute
    previousMillis = currentMillis;
  }
}

void update_oled() {
//  if (i == 121) {
//    i = 0;   
//  }
  if (min_y == max_y) {
    min_y = floor(value*0.5);
    max_y = ceil(value*1.5);
    min_val = value;
    max_val = value;
  }
  if (value > max_val) {
    max_val = value;
    max_y = ceil(value*1.5);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.clearDisplay();
    display.println("Temp:");
    display.drawLine(0, 19, 0, 60, WHITE);
    display.setTextSize(1);
    display.setCursor(3, 16);
    display.println(String(max_y));
    display.setCursor(3, 57);
    display.println(String(min_y));
    display.display();  
  }
  else if (value < min_val) {
    min_val = value;
    min_y = floor(value*0.5);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.clearDisplay();
    display.println("Temp:");
    display.drawLine(0, 19, 0, 60, WHITE);
    display.setTextSize(1);
    display.setCursor(3, 16);
    display.println(String(max_y));
    display.setCursor(3, 57);
    display.println(String(min_y));
    display.display();  
  }
  else {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.clearDisplay();
    display.println("Temp:");
    display.drawLine(0, 19, 0, 60, WHITE);
    display.setTextSize(1);
    display.setCursor(3, 16);
    display.println(String(max_y));
    display.setCursor(3, 57);
    display.println(String(min_y));
    display.display();  
  }
}
