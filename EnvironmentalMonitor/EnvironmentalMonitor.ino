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

  ALTER WIRING FOR DAISY-CHAINING I2C DEVICES!!!!!

  add scaling!

  check array sizes

  increment index
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define OLED_RESET 4
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
Adafruit_SSD1306 display(OLED_RESET);
LiquidCrystal_I2C LCD(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int temp_array[121];
int pres_array[121];
int hum_array[121];
int min_temp_y = 0;
int max_temp_y = 0;
int min_hum_y = 0;
int max_hum_y = 0;
int min_pres_y = 0;
int max_pres_y = 0;
int min_temp_val;
int max_temp_val;
int min_hum_val;
int max_hum_val;
int min_pres_val;
int max_pres_val;
float val_temp;
float val_hum;
float val_pres;
float val_alt;
unsigned long previousMillis = 0;
int index = 0;

void setup()   {
  bme.begin();
  read_sensor();
  
  LCD.begin(20, 4);
  LCD.clear();
  LCD.backlight();//fix later
  LCD.setCursor(0, 0);
  LCD.print("Temp: "+String(val_temp));
  LCD.setCursor(0, 1);
  LCD.print("hum: "+String(val_hum));
  LCD.setCursor(0, 2);
  LCD.print("pres: "+String(val_pres));
  LCD.setCursor(0, 3);
  LCD.print("alt: "+String(val_alt));

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void update_lcd() {
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Temp: "+String(val_temp));
  LCD.setCursor(0, 1);
  LCD.print("hum: "+String(val_hum));
  LCD.setCursor(0, 2);
  LCD.print("pres: "+String(val_pres));
  LCD.setCursor(0, 3);
  LCD.print("alt: "+String(val_alt));
}

void read_sensor() {
  val_temp = bme.readTemperature();
  val_pres = bme.readPressure() / 100.0F;
  val_alt = bme.readAltitude(SEALEVELPRESSURE_HPA);
  val_hum = bme.readHumidity();
}

void loop() {
  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis >= 10000) {
//    //refresh OLED
//    //check light -- do this last
//    previousMillis = currentMillis;
//  }
  if (currentMillis - previousMillis >= 60000) {
    previousMillis = currentMillis;
    //sample sensor
    read_sensor();
    //update lcd
    update_lcd();
    //check if there is space in array
    if (index <= 120) {
      //array still has space
      temp_array[index] = round(val_temp);
      pres_array[index] = round(val_pres);
      hum_array[index] = round(val_hum);
      index+=1;
    }
    else {
      for (int i=0; i<120; i++) {
        temp_array[i] = temp_array[i+1];
        pres_array[i] = pres_array[i+1];
        hum_array[i] = hum_array[i+1];
      }
      temp_array[120] = round(val_temp);
      pres_array[120] = round(val_pres);
      hum_array[120] = round(val_hum);
    }
  temp_oled();
  }
}

void temp_oled() {
  //update min, max, and scaling of window
  if (min_temp_y == max_temp_y) {
    min_temp_y = floor(val_temp * 0.5);
    max_temp_y = ceil(val_temp * 1.5);
    min_temp_val = val_temp;
    max_temp_val = val_temp;
  }
  if (val_temp > max_temp_val) {
    max_temp_val = val_temp;
    max_temp_y = ceil(val_temp * 1.5);
  }
  if (val_temp < min_temp_val) {
    min_temp_val = val_temp;
    min_temp_y = floor(val_temp * 0.5);
  }
  //array isn't full, or perfectly full, so just plot what's there
  if (index-1 <= 120) {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.clearDisplay();
    display.println("Temp:");
    display.drawLine(0, 19, 0, 60, WHITE);
    display.setTextSize(1);
    display.setCursor(3, 16);
    display.println(String(max_temp_y));
    display.setCursor(3, 57);
    display.println(String(min_temp_y));
    for (int i=0; i<=index-1; i++) {
      display.drawPixel(i+1, 41*(max_temp_y - temp_array[i])/(max_temp_y - min_temp_y) + 19, WHITE);// the formula scales the y-value to the correct range, customized for 128x64 display.
    }
    display.display();
  }
  //array is full
  else {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.clearDisplay();
    display.println("Temp:");
    display.drawLine(0, 19, 0, 60, WHITE);
    display.setTextSize(1);
    display.setCursor(3, 16);
    display.println(String(max_temp_y));
    display.setCursor(3, 57);
    display.println(String(min_temp_y));
    for (int i=0; i<=120; i++) {
      display.drawPixel(i+1, 41*(max_temp_y - temp_array[i])/(max_temp_y - min_temp_y) + 19, WHITE);
    }
    display.display();
  }
}
